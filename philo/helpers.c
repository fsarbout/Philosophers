/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:15:18 by fsarbout          #+#    #+#             */
/*   Updated: 2022/02/12 22:37:26 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_(void)
{
	printf("\e[1;31mError \033[0m\n");
	return (-1);
}

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_usec / 1000 + current_time.tv_sec * 1000));
}

void	print_status(char *status, char *color, t_philos *ph, int id)
{
	long	time;

	pthread_mutex_lock(&ph->data->o_mutex);
	time = get_time() - ph->data->start_time;
	printf("%s", color);
	printf("%ld ", time);
	printf("%d ", id + 1);
	printf("%s", status);
	printf("\033[0m\n");
	pthread_mutex_unlock(&ph->data->o_mutex);
}

void	ft_free(t_philos *philo)
{
	if (philo->data->f_mutex)
		free(philo->data->f_mutex);
	if (philo->data->e_mutex)
		free(philo->data->e_mutex);
	if (philo->data->th)
		free(philo->data->th);
	if (philo->data)
		free(philo->data);
	if (philo)
		free(philo);
}

void	u_sleep(int usec)
{
	long	start_time;

	start_time = get_time();
	usleep(usec - 10000);
	while (((get_time() - start_time) * 1000) < usec)
		;
}
