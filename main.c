/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 20:30:43 by fsarbout          #+#    #+#             */
/*   Updated: 2021/07/12 20:54:54 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine(void *arg)
{
    t_philos *philo;
    philo = (t_philos *)arg;
    
    // philo = malloc(sizeof(t_philos *) * )
    printf("thread outside %d \n", philo->data.num_forks);
    while (philo->data.num_of_philos)
    {
        if (philo->data.num_forks % 2 == 0)
        {
            pthread_mutex_lock(&philo->data.mutex);
            printf("thread %d \n",philo->data.num_forks );
            pthread_mutex_unlock(&philo->data.mutex);
        }
    }
    return 0;    
}

int main(int ac, char **av)
{
    t_data *data;
    t_philos *philo;
    // int i = 8;

    if (ac != 5 && ac != 6)
        exit_("Error : number of arguments", 1);
    fill_data(&data, &philo, av, ac);
    // int philo_n = data->num_of_philos;
    // while (philo_n--)
    // {
    //     pthread_create(&data.th, NULL, &routine, &data);
    //     pthread_join(data.th, NULL);
    // }
    printf ("hello\n");
    // print_status(data);
}