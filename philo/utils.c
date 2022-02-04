/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:15:18 by fsarbout          #+#    #+#             */
/*   Updated: 2022/02/01 18:39:29 by fsarbout         ###   ########.fr       */
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

int exit_()
{
	printf("\e[1;31mError \033[0m\n");
	return (-1);
}

int is_pair(int i)
{
	if ((i % 2) == 0)
		return (1);
	return (0);
}

int fill_data(t_philos *philo, char **av, int ac, t_data *data)
{
	(void)philo;

	if (ft_atoi(av[1]) == -1 || ft_atoi(av[2]) == -1 || ft_atoi(av[3]) == -1 || ft_atoi(av[4]) == -1 || (ac == 6 && ft_atoi(av[5]) == -1))
		return -1;
	data->nb_philos = ft_atoi(av[1]);
	if (data->nb_philos == 0 || data->nb_philos == 1)
		return -1;
	data->time_to_die = ft_atoi(av[2]) * TO_MICRO_S;
	data->time_to_eat = ft_atoi(av[3]) * TO_MICRO_S;
	data->time_to_sleep = ft_atoi(av[4]) * TO_MICRO_S;
	if (ac == 6)
		data->n_necessity_to_eat = ft_atoi(av[5]);
	data->num_forks = data->nb_philos;
	data->f_mutex = malloc(sizeof(pthread_mutex_t) * data->num_forks);
	data->th = malloc(sizeof(pthread_t) * data->nb_philos);

	return (0);
}

// ! get time function

long get_time()
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_usec / 1000 + current_time.tv_sec * 1000));
}

// ! print status function

void print_status(char *status, char *color, t_philos *ph)
{
	long time;

	pthread_mutex_lock(&ph->data->o_mutex);
	time = get_time() - ph->data->start_time;
	printf("%s", color);
	printf("%ld ", time);
	printf("%d ", ph->id + 1);
	printf("%s", status);
	printf("\033[0m\n");
	pthread_mutex_unlock(&ph->data->o_mutex);
}

// ! free function

void ft_free(t_philos *philo)
{
	if (philo->data->f_mutex)
		free(philo->data->f_mutex);
	if (philo->data->th)
		free(philo->data->th);
	if (philo->data)
		free(philo->data);
	if (philo)
		free(philo);
}

// ! check death function

int check_death(t_philos *philo, t_data *data)
{
	int i;

	while (1)
	{
		usleep(10);
		printf("check death\n");
		i = 0;
		while (i < data->nb_philos)
		{
			printf("check death 2\n");
			printf("i : %d\n", i );
			if (data->time_to_eat >= data->time_to_die)
			{
				print_status("died", "\e[1;31m", philo);
				printf("2\n");
				exit(1);
			}
			printf(" philo[i]->last_eat = %ld\n", philo[i].last_eat);
			printf(" id = %d\n", philo[i].id);
			printf(" current time = %ld\n", get_time());

			printf(" philo[i]->last_eat - currentTime = %ld\n", (get_time() - philo[i].last_eat));
			printf(" time to die = %d\n", data->time_to_die);
			// philo[i].last_eat
			if (data->time_to_die <= (get_time() - philo[i].last_eat))
			{
				print_status("died", "\e[1;31m", philo);
				printf("1\n");
				exit(1);
			}
			i++;
		}
		return (0);
	}
}

// ! mutex init function

void mutex_init(t_data *data)
{
	int i = 0;

	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->f_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->o_mutex, NULL);
	pthread_mutex_init(&data->e_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
}

// ! fix usleep

void u_sleep(int usec)
{
	long start_time;

	start_time = get_time();
	usleep(usec - 20000);
	while (get_time() - start_time < usec)
		;
}