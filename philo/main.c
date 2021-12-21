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

// ! free function

void ft_free(t_philos *philo)
{
    if (philo->data->f_mutex)
        free(philo->data->f_mutex);
    if (philo->data)
        free(philo->data);
    if (philo)
        free(philo);
}

// ! gettime function

int get_time()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_usec);
}

// ! check death function

int check_death(t_philos *philo)
{
    int gettime;
    if (philo->data->time_to_eat >= philo->data->time_to_die)
        return (1);
    gettime = get_time();
    if (philo->data->time_to_die <= (philo->last_eat - gettime))
        return (1);
    return (0);
}

// ! take forks fucntion

void take_forks(t_philos *ph)
{
    pthread_mutex_lock(&ph->data->f_mutex[ph->id]);
    ph->has_forks++;
    printf("\e[1;33m%d ", get_time());
    printf("\e[1;33m%d has taken a fork\033[0m\n", ph->id);
    pthread_mutex_lock(&ph->data->f_mutex[ph->id + 1]);
    ph->has_forks++;
    printf("\e[1;33m%d ", get_time());
    printf("\e[1;33m%d has taken a fork\033[0m\n", ph->id);
}

// ! eat function

void eating(t_philos *ph)
{
    if (ph->has_forks == 2)
    {
        printf("\e[1;32m%d ", get_time());
        printf("\e[1;32m%d is eating\033[0m\n", ph->id);
        ph->last_eat = get_time();
    }
    pthread_mutex_unlock(&ph->data->f_mutex[ph->id]);
    pthread_mutex_unlock(&ph->data->f_mutex[ph->id + 1]);
}

// ! thinking fucntion

void thinking(t_philos *ph)
{
    printf("\e[1;32m%d ", get_time());
    printf("\e[1;34m%d is thinking\033[0m\n", ph->id);
}

// ! sleeping fucntion

void sleeping(t_philos *ph)
{
    printf("\e[1;32m%d ", get_time());
    printf("\033[1;35m%d is seelping\033[0m\n", ph->id);
    // sleep(ph->data->time_to_sleep);
}

// ! dead fucntion

void is_dead(t_philos *ph)
{
    printf("\e[1;31m%d ", get_time());
    printf("\e[1;31m%d died\033[0m\n", ph->id);
    // sleep(ph->data->time_to_sleep);
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
    t_philos *philo = NULL;
    int i = 0;

    if (ac != 5 && ac != 6)
        exit_("\e[1;31mError : number of arguments\033[0m", 1);

    philo = malloc(sizeof(t_philos));
    philo->data = malloc(sizeof(t_data));
    fill_data(philo, av, ac);
    philo->data->f_mutex = malloc(sizeof(pthread_mutex_t) * philo->data->num_forks);
    //
    while (i < philo->data->nb_philos)
    {
        pthread_mutex_init(&philo->data->f_mutex[i], NULL);
        i++;
    }
    i = 0;
    while (1)
    {
        while (i < philo->data->nb_philos)
        {
            pthread_create(&philo->data->th, NULL, routine, philo);
            pthread_join(philo->data->th, NULL);
            if (check_death(philo))
            {
                is_dead(philo);
                ft_free(philo);
                return 0;
            }
            philo->id = i++;
        }
    }
    ft_free(philo);
    return 0;
}