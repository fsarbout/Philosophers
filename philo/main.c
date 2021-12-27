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
// todo : update usleep

// ! gettime function

long get_time()
{
    struct timeval current_time;

    gettimeofday(&current_time, NULL);
    return ((current_time.tv_usec / 1000 + current_time.tv_sec * 1000));
}

// ! print status function

void    print_status(char *status,char *color,t_philos *ph)
{
    long time;
    // (void)status;
    // (void)color;
    // (void)ph;
    
    pthread_mutex_lock(&ph->data->o_mutex);
    time = get_time() - ph->data->start_time;
    printf("%s", color);
    printf ("%ld ", time);
    printf("%d ", ph->id + 1);
    printf("%s", status);
    printf("\033[0m\n");
    pthread_mutex_unlock(&ph->data->o_mutex);
}

// ! free function

void ft_free(t_philos *philo)
{
    if (philo->data->f_mutex)
        free(philo->data->f_mutex);
    if (philo->data->th)
        free(philo->data->th);
    if (philo->data)
        free(philo->data);
    if (philo)
        free(philo);
}

// ! check death function

int check_death(t_philos *philo, t_data *data)
{
    if (data->time_to_eat >= data->time_to_die)
       {printf("2\n"); return (1); }
    if (data->time_to_die <= (philo->last_eat - get_time()))
    {
        printf("3\n"); 
        return (1);
    }
    return (0);
}

// ! main function

int main(int ac, char **av)
{
    t_philos *philo;
    t_data *data;

    if (ac != 5 && ac != 6)
        exit_("\e[1;31mError : number of arguments\033[0m", 1);
    philo = NULL;
    data = malloc(sizeof(t_data));
    mutex_init(philo, data);
    fill_data(philo, av, ac, data);
	philo = malloc(sizeof(t_philos) * data->nb_philos);
    if (data->nb_philos == 0)
    {
        exit_("\e[1;31mError : no philo exists\033[0m", 1);
        ft_free(philo);
    }
    start_simi(philo, data);
}

// ! mutex init function

void mutex_init(t_philos *philo, t_data *data)
{
    (void)philo;
    int i = 0;

    while (i < data->nb_philos)
    {
        pthread_mutex_init(&data->f_mutex[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->o_mutex, NULL);
    pthread_mutex_init(&data->e_mutex, NULL);
}

// ! start similation function

void start_simi(t_philos *philo, t_data *data)
{
    int i ;

    i = 0;
   data->start_time = get_time();


    while (i < data->nb_philos)
    {
        philo->id = i;
        philo[i].data = data;
        pthread_create(&data->th[i], NULL, &routine, &philo[i]);
        usleep(800);
        i++;
    }
    if (check_death(philo, data))
    {
        is_dead(philo);
        // print_status("died", "\e[1;31m", philo);
        // ft_free(philo);
        return ; 
    }
    // ft_free(philo);
}