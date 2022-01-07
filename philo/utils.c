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
		return(exit_());
	if (*s == '-')
		return(exit_());
	else if (*s == '+')
		s++;
	while ((*s <= '9') && (*s >= '0'))
	{
		a = a * 10 + *s - '0';
		if (a > 4294967296 && sign == 1)
			return(exit_());
		if (a > 4294967296 && sign == -1)
			return(exit_());
		s++;
	}
	return ((int)a * sign);
}

int exit_()
{
		printf("\e[1;31mError \033[0m\n");
		return(-1);
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

	if ( ft_atoi(av[1]) == -1 || ft_atoi(av[2]) == -1 || ft_atoi(av[3]) == -1 
		|| ft_atoi(av[4]) == -1 || (ac == 6 && ft_atoi(av[5]) == -1))
		return -1;
	data->nb_philos = ft_atoi(av[1]);
	if (data->nb_philos == 0)
		return -1;
	data->time_to_die = ft_atoi(av[2]) * TO_MICRO_S;
	data->time_to_eat = ft_atoi(av[3]) * TO_MICRO_S;
	data->time_to_sleep = ft_atoi(av[4]) * TO_MICRO_S;
	if (ac == 6)
			data->n_necessity_to_eat = ft_atoi(av[5]);
	data->num_forks = data->nb_philos;
    data->f_mutex = malloc(sizeof(pthread_mutex_t) * data->num_forks);
	// pthread_mutex_init(&data->f_mutex[900], NULL);

    // data->f_mutex = malloc(sizeof(pthread_mutex_t) * 1);
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

void    print_status(char *status,char *color,t_philos *ph)
{
    long time;
    
    pthread_mutex_lock(&ph->data->o_mutex);
    time = get_time() - ph->data->start_time;
    printf("%s", color);
    printf ("%ld ", time);
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
    // pthread_mutex_lock(&philo->data->o_mutex);
    if (data->time_to_eat >= data->time_to_die)
       {printf("2\n"); return (1); }
    if (data->time_to_die <= (philo->last_eat - get_time()))
    {
        printf("3\n"); 
        return (1);
    }
    // pthread_mutex_unlock(&philo->data->o_mutex);
    return (0);
}



// ! mutex init function

void mutex_init(t_philos *philo, t_data *data)
{
    (void)philo;
    int i = 0;

		// printf("\e[1;31mnum of f mutexes: %d \033[0m\n", data->nb_philos);
    while (i < data->nb_philos)
    {
        pthread_mutex_init(&data->f_mutex[i], NULL);
		// exit
        i++;
    }
    pthread_mutex_init(&data->o_mutex, NULL);
    pthread_mutex_init(&data->e_mutex, NULL);
}
