#include "philo.h"

// ! take forks fucntion

// todo : fix ph->id from 0 to -9859349543 problem 
// todo : check death 
// todo : update usleep
// todo : fix ft_free

void take_forks(t_philos *ph)
{
    // pthread_mutex_lock(&ph->data->f_mutex[ph->id]);
	printf ("id : %d\n", ph->id);
    print_status("has taken a fork", "\e[1;33m", ph);
    // pthread_mutex_lock(&ph->data->f_mutex[ph->id + 1]);
    printf("fork 1 id %d\n", ph->id);
    printf("fork 2 id %d\n", ph->id + 1);
    ph->has_forks = 2;
    print_status("has taken a fork", "\e[1;33m", ph);
}

// ! eat function

void eating(t_philos *ph)
{

	// printf("hello 2\n");
    if (ph->has_forks == 2)
    {
        pthread_mutex_lock(&ph->data->e_mutex);
        print_status("is eating", "\e[1;32m", ph);
        ph->last_eat = get_time();
        ph->eat_nb++;
        // pthread_mutex_unlock(&ph->data->f_mutex[ph->id]);
        // pthread_mutex_unlock(&ph->data->f_mutex[ph->id + 1]);
        pthread_mutex_unlock(&ph->data->e_mutex);
    }
    usleep(ph->data->time_to_eat);
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

    while (1)
    {
        take_forks(ph);
        eating(ph);
        sleeping(ph);
        thinking(ph);
    }

    return NULL;
}