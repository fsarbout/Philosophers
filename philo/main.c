/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 20:30:43 by fsarbout          #+#    #+#             */
/*   Updated: 2021/12/03 14:26:23 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// todo : time to eat, time to sleep and time to think
// todo : infinite loop untill someone dies
// todo : start from id 1 , and check why it stops at (id - 2)
// todo : do I need any other mutex (apart from the forks)

// ! gettime function

int get_time()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_usec);
}

// ! print status function

void    print_status(char *status,char *color,t_philos *ph)
{
    pthread_mutex_lock(&ph->data->e_mutex);
    printf("%s", color);
    printf ("%d " , get_time());
    printf("%d ", ph->id);
    printf("%s", status);
    printf("\033[0m\n");
    pthread_mutex_unlock(&ph->data->e_mutex);
}

// ! free function

void ft_free(t_philos *philo, pthread_t *th)
{
    if (philo->data->f_mutex)
        free(philo->data->f_mutex);
    if (philo->data)
        free(philo->data);
    if (philo)
        free(philo);
    if (th)
        free(th);
}

// ! check death function

int check_death(t_philos *philo)
{
    int gettime;
    if (philo->data->time_to_eat >= philo->data->time_to_die)
       {printf("2\n"); return (1); }
    gettime = get_time();
    printf("time to die %d\n", philo->data->time_to_die);
    printf("last eat %d\n", philo->last_eat);
    if (philo->data->time_to_die <= (philo->last_eat - gettime))
    {
        printf("time to die %d\n", philo->data->time_to_die);
        printf("last eat %d\n", philo->last_eat);
        printf("get time %d\n", gettime);
        printf("last eat - gettime %d\n", (philo->last_eat - gettime)); 
        printf("3\n"); 
        return (1);
    }
    return (0);
}

// ! take forks fucntion

void take_forks(t_philos *ph)
{
    pthread_mutex_lock(&ph->data->f_mutex[ph->id -1]);
    printf("fork 1 id %d\n", ph->id - 1);
    ph->has_forks = 1;
    print_status("has taken a fork", "\e[1;33m", ph);
    pthread_mutex_lock(&ph->data->f_mutex[ph->id]);
    printf("fork 2 id %d\n", ph->id);
    ph->has_forks = 2;
    print_status("has taken a fork", "\e[1;33m", ph);
}

// ! eat function

void eating(t_philos *ph)
{
    if (ph->has_forks == 2)
    {
        print_status("is eating", "\e[1;32m", ph);
        ph->last_eat = get_time();
        ph->eat_nb++;
    }
    usleep(ph->data->time_to_eat);
    pthread_mutex_unlock(&ph->data->f_mutex[ph->id - 1]);
    pthread_mutex_unlock(&ph->data->f_mutex[ph->id]);
}

// ! thinking fucntion

void thinking(t_philos *ph)
{
    print_status("is thinking", "\e[1;34m", ph);
}

// ! sleeping fucntion

void sleeping(t_philos *ph)
{
    print_status("is sleeping", "\e[1;35m", ph);
    usleep(ph->data->time_to_sleep);
}

// ! dead fucntion

void is_dead(t_philos *ph)
{
    print_status("died", "\e[1;31m", ph);
}

// ! routine function

void *routine(void *arg)
{
    t_philos *ph;
    ph = (t_philos *)arg;

    take_forks(ph);
    eating(ph);
    sleeping(ph);
    thinking(ph);
    usleep(800);

    return 0;
}

// ! main function

int main(int ac, char **av)
{
    pthread_t *th;
    t_philos *philo;

    if (ac != 5 && ac != 6)
        exit_("\e[1;31mError : number of arguments\033[0m", 1);
    philo = malloc(sizeof(t_philos));
    philo->data = malloc(sizeof(t_data));
    fill_data(philo, av, ac);
    if (philo->data->nb_philos == 0)
    {
        exit_("\e[1;31mError : no philo exists\033[0m", 1);
        ft_free(philo, 0);
    }
    philo->data->f_mutex = malloc(sizeof(pthread_mutex_t) * philo->data->num_forks);
    th = malloc(sizeof(pthread_t) * philo->data->nb_philos);
    mutex_init(philo);
    start_simi(philo, th);
}

// ! mutex init function 

void mutex_init(t_philos *philo)
{
    int i = 0;

    while (i < philo->data->nb_philos)
    {
        pthread_mutex_init(&philo->data->f_mutex[i], NULL);
        i++;
    }
    pthread_mutex_init(&philo->data->e_mutex, NULL);
}

// ! start similation function

void start_simi(t_philos *philo, pthread_t *th)
{
    int i ;

    while (1)
    {
        i = 1;
        while (i <= philo->data->nb_philos)
        {
            philo->id = i++;
            philo->start_time = get_time();
            if (pthread_create(&th[philo->id - 1], NULL, routine, philo))
                exit_("\e[1;31mError : pthread_create\033[0m", 1);
            if (pthread_join(th[philo->id - 1], NULL))
                exit_("\e[1;31mError : pthread_join \033[0m", 1);
            if (check_death(philo))
            {
                is_dead(philo);
                ft_free(philo, th);
                return ;
            }
        }
        if (philo->id == philo->data->nb_philos)
            philo->id = 1;
        printf("\e[1;37m***********************************************************************\033[0m\n");
    }
    ft_free(philo, th);
}