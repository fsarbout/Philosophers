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

void    *routine(void *arg)
{
    t_philos *philo;
    philo = (t_philos *)arg;
    
    philo = malloc(sizeof(t_philos *) * philo->data.nb_philos);
    printf("thread outside %d \n", philo->data.num_forks);
    while (philo->data.nb_philos)
    {
        if (philo->data.num_forks % 2 == 0)
        {
            pthread_mutex_lock(&philo->data.mutex);
            printf("thread %d \n",philo->data.num_forks );
            pthread_mutex_unlock(&philo->data.mutex);
        }
    }
    print_status(&philo->data);
    return 0;    
}

int main(int ac, char **av)
{
    t_data *data = NULL;
    t_philos *philo = NULL;
    // int i = 8;

    if (ac != 5 && ac != 6)
        exit_("\e[1;31mError : number of arguments\033[0m", 1);
    data = malloc(sizeof(t_data));
    fill_data(data, &philo, av, ac);
// 
    int philo_n = data->nb_philos;
    while (philo_n--)
    {
        pthread_create(&data->th, NULL, &routine, &data);
        pthread_join(&data->th, NULL);
    }
//  
    printf ("hello\n");
    print_status(data);
}