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

// todo : fix check death (supervisor)
// todo : correct usleep, (usleep adds 5-10 micro )

// ! main function

int main(int ac, char **av)
{
    t_philos *philo;
    t_data *data;

    if (ac != 5 && ac != 6)
        return(exit_());
    philo = NULL;
    data = malloc(sizeof(t_data));
    if (fill_data(philo, av, ac, data) == -1)
        return 0;
    mutex_init(philo, data);
	philo = malloc(sizeof(t_philos) * data->nb_philos);

    start_simi(philo, data);
    // if (check_death(philo, data))
    // {
    //     is_dead(philo);
    //     // print_status("died", "\e[1;31m", philo);
    //     // ft_free(philo);
    //     return 0; 
    // }
}

// ! start similation function

void start_simi(t_philos *philo, t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_time();

    while (i < data->nb_philos)
    {
        philo[i].id = i;
        philo[i].data = data;
        pthread_create(&data->th[i], NULL, &routine, &philo[i]);
        usleep(800);
        i++;

        
        // check_death(philo, data)
    }
    i = 0;

    // while (i < data->nb_philos)
    // {

    //     // pthread_join(data->th[i], NULL);
    //     i++;
    // }

    while (1)
    {
        if (check_death(philo, data))
        {
            print_status("died", "\e[1;31m", philo);
            pthread_mutex_lock(&data->o_mutex);
            // is_dead(philo);
            // pthread_mutex_unlock(&data->o_mutex);
            // ft_free(philo);
            return ; 
        }
        /* code */
    }
    
    // ft_free(philo);
}