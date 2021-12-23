/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:15:18 by fsarbout          #+#    #+#             */
/*   Updated: 2021/12/03 14:22:19 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int not_number(const char *str)
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

int ft_atoi(const char *s)
{
	int sign;
	long a;

	sign = 1;
	a = 0;
	while (*s == ' ')
		s++;
	if (not_number(s))
		exit_("Error : invalid args", 1);
	if (*s == '-')
		exit_("Error : invalid args", 1);
	else if (*s == '+')
		s++;
	while ((*s <= '9') && (*s >= '0'))
	{
		a = a * 10 + *s - '0';
		if (a > 4294967296 && sign == 1)
			exit_("Error : args limit", 1);
		if (a > 4294967296 && sign == -1)
			exit_("Error : args limit", 1);
		s++;
	}
	return ((int)a * sign);
}

void exit_(char *string, int error)
{
	if (error == 1)
	{
		printf("\e[1;31m%s\033[0m\n", string);
		exit(1);
	}
	exit(0);
}

int is_pair(int i)
{
	if ((i % 2) == 0)
		return (1);
	return (0);
}

void fill_data(t_philos *philo, char **av, int ac)
{
	philo->data->nb_philos = ft_atoi(av[1]);
	philo->data->time_to_die = ft_atoi(av[2]) * TO_MICRO_S;
	philo->data->time_to_eat = ft_atoi(av[3]) * TO_MICRO_S;
	philo->data->time_to_sleep = ft_atoi(av[4]) * TO_MICRO_S;
	if (ac == 6)
		philo->data->n_necessity_to_eat = ft_atoi(av[5]);
	philo->data->num_forks = philo->data->nb_philos;
	philo->id = 0;
	philo->eat_nb = 0;
	philo->last_eat = 0;
}
