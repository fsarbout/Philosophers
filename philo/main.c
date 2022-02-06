/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 20:30:43 by fsarbout          #+#    #+#             */
/*   Updated: 2022/02/01 18:41:56 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// todo : fix ft_free
// todo : norme 
// todo : fix decalage

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
    mutex_init(data);
	philo = malloc(sizeof(t_philos) * data->nb_philos);
    start_simi(philo, data);
}

// ! start similation function

void start_simi(t_philos *philo, t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_time();

    while (i < data->nb_philos)
    {
        philo[i].eat_nb = 0;
        philo[i].id = i;
        philo[i].last_eat = data->start_time;
        philo[i].data = data;
        pthread_create(&data->th[i], NULL, &routine, &philo[i]);
        usleep(80);
        i++;
    }
    check_death(philo, data);
    ft_free(philo);
}