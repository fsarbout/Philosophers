#include "philo.h"

// ! take forks fucntion

// todo : fix ph->id from 0 to -9859349543 problem
// todo : check death
// todo : update usleep
// todo : fix ft_free

void take_forks(t_philos *ph)
{
    pthread_mutex_lock(&ph->data->f_mutex[ph->id]);
    print_status("has taken a fork", "\e[1;33m", ph);
    printf("on\n");
    printf("ph id %d\n", ph->id);
    if ((ph->id + 1) == ph->data->nb_philos)
    {
        printf("1\n");
        pthread_mutex_lock(&ph->data->f_mutex[0]);
    }
    else{
        printf("2\n");
        pthread_mutex_lock(&ph->data->f_mutex[ph->id + 1]);
    }
    print_status("has taken a fork", "\e[1;33m", ph);
    printf("last seen in is take forks\n");
}

// ! eat function

void eating(t_philos *ph)
{
    pthread_mutex_lock(&ph->data->e_mutex);
    ph->last_eat = get_time();
    print_status("is eating", "\e[1;32m", ph);
    ph->eat_nb++;
    u_sleep(ph->data->time_to_eat);
    pthread_mutex_unlock(&ph->data->f_mutex[ph->id]);
    if ((ph->id + 1) == ph->data->nb_philos)
    {
        printf("11\n");
        pthread_mutex_unlock(&ph->data->f_mutex[0]);
    }
    else
    {
        printf("22\n");
        pthread_mutex_unlock(&ph->data->f_mutex[ph->id + 1]);
    }
    pthread_mutex_unlock(&ph->data->e_mutex);
    printf("last seen in is eating\n");
}

// ! sleeping fucntion

void sleeping(t_philos *ph)
{
    print_status("is sleeping", "\e[1;35m", ph);
    u_sleep(ph->data->time_to_sleep);
    printf("last seen in sleeping\n");
}

// ! dead fucntion

void is_dead(t_philos *ph)
{
    print_status("died", "\e[1;31m", ph);
    printf("last seen in is dead\n");
}

// ! is thinking fucntion

void is_thinking(t_philos *ph)
{
    print_status("is thinking", "\e[1;34m", ph);
    printf("last seen in is thinking\n");
}

// ! routine function

void *routine(void *arg)
{
    t_philos *ph;
    ph = (t_philos *)arg;

    while (1)
    {
        take_forks(ph);
        printf("hello 1\n");
        eating(ph);
        printf("hello 2\n");
        sleeping(ph);
        is_thinking(ph);
        printf("last seen loop routine\n");
    }
    printf("last seen in is routine\n");
    return NULL;
}