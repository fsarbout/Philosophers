#include "philo.h"

// ! take forks fucntion

// 
// todo : check death
// todo : update usleep
// todo : fix ft_free

void take_forks(t_philos *ph)
{
    pthread_mutex_lock(&ph->data->f_mutex[ph->id]);
    print_status("has taken a fork", "\e[1;33m", ph);
    if ((ph->id + 1) == ph->data->nb_philos)
            pthread_mutex_lock(&ph->data->f_mutex[0]);
    else
        pthread_mutex_lock(&ph->data->f_mutex[ph->id + 1]);
    print_status("has taken a fork", "\e[1;33m", ph);
}

// ! eat function

void eating(t_philos *ph)
{
    pthread_mutex_lock(&ph->data->e_mutex[ph->id]);
    ph->last_eat = get_time();
    pthread_mutex_unlock(&ph->data->e_mutex[ph->id]);
    print_status("is eating", "\e[1;32m", ph);
    ph->eat_nb++;
    u_sleep(ph->data->time_to_eat * 1000);
    pthread_mutex_unlock(&ph->data->f_mutex[ph->id]);
    if ((ph->id + 1) == ph->data->nb_philos)
        pthread_mutex_unlock(&ph->data->f_mutex[0]);
    else
        pthread_mutex_unlock(&ph->data->f_mutex[ph->id + 1]);
}

// ! sleeping fucntion

void sleeping(t_philos *ph)
{
    print_status("is sleeping", "\e[1;35m", ph);
    u_sleep(ph->data->time_to_sleep * 1000);
}

// ! dead fucntion

void is_dead(t_philos *ph)
{
    print_status("died", "\e[1;31m", ph);
}

// ! is thinking fucntion

void is_thinking(t_philos *ph)
{
    print_status("is thinking", "\e[1;34m", ph);
}

// ! routine function

void *routine(void *arg)
{
    t_philos *ph;
    ph = (t_philos *)arg;

    while (1)
    {
        take_forks(ph);
        eating(ph);
        sleeping(ph);
        is_thinking(ph);
    }
    return NULL;
}