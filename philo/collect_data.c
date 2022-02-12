/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:26:52 by fsarbout          #+#    #+#             */
/*   Updated: 2022/02/12 20:46:52 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	collect_data(char **av, int ac, t_data *data)
{
	if (ft_atoi(av[1]) == -1 || ft_atoi(av[2]) == -1 || ft_atoi(av[3]) == -1
		|| ft_atoi(av[4]) == -1 || (ac == 6 && ft_atoi(av[5]) == -1))
		return (-1);
	data->nb_philos = ft_atoi(av[1]);
	if (data->nb_philos == 0)
		return (-1);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->n_necessity_to_eat = ft_atoi(av[5]);
	if (data->n_necessity_to_eat == 0)
		return (-1);
	data->num_forks = data->nb_philos;
	data->f_mutex = malloc(sizeof(pthread_mutex_t) * data->num_forks);
	data->e_mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	data->th = malloc(sizeof(pthread_t) * data->nb_philos);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	not_number(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!(ft_isdigit(*str)))
			return (1);
		str++;
	}
	return (0);
}

int	ft_atoi(const char *s)
{
	int		sign;
	long	a;

	sign = 1;
	a = 0;
	while (*s == ' ')
		s++;
	if (not_number(s))
		return (exit_());
	if (*s == '-')
		return (exit_());
	else if (*s == '+')
		s++;
	while ((*s <= '9') && (*s >= '0'))
	{
		a = a * 10 + *s - '0';
		if (a > 4294967296 && sign == 1)
			return (exit_());
		if (a > 4294967296 && sign == -1)
			return (exit_());
		s++;
	}
	return ((int)a * sign);
}

int	is_pair(int i)
{
	if ((i % 2) == 0)
		return (1);
	return (0);
}
