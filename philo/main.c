/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 20:30:43 by fsarbout          #+#    #+#             */
/*   Updated: 2022/02/10 01:11:44 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philos	*philo;
	t_data		*data;

	if (ac != 5 && ac != 6)
		return (exit_());
	philo = NULL;
	data = malloc(sizeof(t_data));
	if (collect_data(av, ac, data) == -1)
		return (0);
	mutex_init(data);
	philo = malloc(sizeof(t_philos) * data->nb_philos);
	start_simi(philo, data);
	ft_free(philo);
}

void	start_simi(t_philos *philo, t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_philos)
	{
		philo[i].eat_nb = 0;
		philo[i].id = i;
		philo[i].last_eat = data->start_time;
		philo[i].data = data;
		pthread_create(&data->th[i], NULL, &routine, &philo[i]);
		usleep(100);
		i++;
	}
	check_death(philo, data);
}

int	check_death(t_philos *philo, t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		usleep(10);
		while (i < data->nb_philos)
		{
			if (data->time_to_die <= ((get_time() - philo[i].last_eat)))
			{
				print_status("died", "\e[1;31m", philo);
				pthread_mutex_lock(&data->o_mutex);
				return (1);
			}
			if (philo->data->n_necessity_to_eat > 0 && check_nb_eat(philo))
				return (1);
		}
		i++;
	}
}

void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->f_mutex[i], NULL);
		pthread_mutex_init(&data->e_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->o_mutex, NULL);
}

int	check_nb_eat(t_philos *philo)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	while (i < philo->data->nb_philos)
	{
		if (philo[i].eat_nb >= philo->data->n_necessity_to_eat)
			done++;
		i++;
	}
	if (done == philo->data->nb_philos)
		return (1);
	return (0);
}
