#include "philo.h"

// ! take forks fucntion

// todo : fix ph->id from 0 to -9859349543 problem
// todo : check death
// todo : update usleep
// todo : fix ft_free

void take_forks(t_philos *ph)
{
    // printf("id: %d\n", ph->id);
    // printf("id + 1: %d\n", ph->id + 1);
    pthread_mutex_lock(&ph->data->f_mutex[ph->id]);
    // printf(" size %ld\n", sizeof(ph->data->f_mutex));
    print_status("has taken a fork", "\e[1;33m", ph);
    if ((ph->id + 1) == ph->data->nb_philos)
        pthread_mutex_lock(&ph->data->f_mutex[0]);
    else
        pthread_mutex_lock(&ph->data->f_mutex[ph->id + 1]);

    // pthread_mutex_lock(&ph->data->f_mutex[ph->id + 1]);
    print_status("has taken a fork", "\e[1;33m", ph);
}

// ! eat function

void eating(t_philos *ph)
{
    pthread_mutex_lock(&ph->data->e_mutex);
    ph->last_eat = get_time();
    print_status("is eating", "\e[1;32m", ph);
    ph->eat_nb++;
    usleep(ph->data->time_to_eat);
    pthread_mutex_unlock(&ph->data->f_mutex[ph->id]);
     if ((ph->id + 1) == ph->data->nb_philos)
        pthread_mutex_unlock(&ph->data->f_mutex[0]);
    else
        pthread_mutex_unlock(&ph->data->f_mutex[ph->id + 1]);
    pthread_mutex_unlock(&ph->data->e_mutex);
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

    while (1)
    {
        take_forks(ph);
        eating(ph);
        sleeping(ph);
        print_status("is thinking", "\e[1;34m", ph);
        // break;
    }
    return NULL;
}