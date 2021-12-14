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

// ! take forks fucntion

void take_forks(t_philos *ph)
{
    pthread_mutex_lock(&ph->data.f_mutex);
    printf ("%d has taken a fork\n" , ph->id);
    pthread_mutex_unlock(&ph->data.f_mutex);
}

// ! routine function

void    *routine(void *arg)
{
    t_philos *ph;
    ph = (t_philos *)arg;
    
    printf("\033[0;31m thread outside %d  \033[0m\n", ph->data.num_forks);
    while ( ph->data.nb_philos > 0)
    {
        take_forks( ph);
        sleep(1);
        ph->data.nb_philos--;
    }

    return 0;    
}

// ! main function

int main(int ac, char **av)
{
    // t_data *data = NULL;
    t_philos *philo = NULL;
    // int i = 8;

    if (ac != 5 && ac != 6)
        exit_("\e[1;31mError : number of arguments\033[0m", 1);
    // data = malloc(sizeof(t_data));
    philo = malloc(sizeof(t_philos));
    fill_data(philo, av, ac);
// 
    int philo_n = philo->data.nb_philos;
    printf("  n philp %d\n", philo_n);
    int i = 0;
    while (i < philo_n)
    {
        pthread_create(&philo->data.th, NULL, routine,philo);
        pthread_join(philo->data.th, NULL); 
        // break;
        philo->id = i;
        i++;   
    }
    // print_status(philo->data);
    if (philo)
        free(philo);
}