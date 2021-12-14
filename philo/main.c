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
    t_data *data;
    data = (t_data *)arg;
    
    printf("\033[0;31m thread outside %d  \033[0m\n", data->num_forks);
    while (data->nb_philos > 0)
    {
        if (data->num_forks % 2 == 0)
        {
            pthread_mutex_lock(&data->mutex);
            printf("thread %d \n",data->num_forks);
            pthread_mutex_unlock(&data->mutex);
        }
        data->nb_philos--;
    }
    // print_status(data);
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
    printf("  n philp %d\n", philo_n);
    int i = 0;
    while (i < philo_n)
    {
        pthread_create(&data->th, NULL, routine,data);
        pthread_join(data->th, NULL);
        // break;
        i++;   
    }
// 
    printf ("hello\n");
    print_status(data);
}