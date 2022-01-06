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

// ! main function

int main(int ac, char **av)
{
    t_philos *philo;
    t_data *data;

    if (ac != 5 && ac != 6)
        return(exit_());
    philo = NULL;
    data = malloc(sizeof(t_data));
    mutex_init(philo, data);
    if (fill_data(philo, av, ac, data) == -1)
        return 0;
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
        philo->id = i;
        philo[i].data = data;
        pthread_create(&data->th[i], NULL, &routine, &philo[i]);
        usleep(800);
        i++;
        printf ("philo->id: %d\n", philo->id);
        printf ("i: %d\n", i);
        // check_death(philo, data);
    }
    // if (check_death(philo, data))
    // {
    //     pthread_mutex_lock(&data->o_mutex);
    //     // is_dead(philo);
    //     // pthread_mutex_unlock(&data->o_mutex);
    //     print_status("died", "\e[1;31m", philo);
    //     // ft_free(philo);
    //     return ; 
    // }
    // ft_free(philo);
}