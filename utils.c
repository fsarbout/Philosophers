/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:15:18 by fsarbout          #+#    #+#             */
/*   Updated: 2021/07/12 11:31:12 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	int		sign;
	long	a;

	sign = 1;
	a = 0;
	while (*s == ' ' || (*s <= 13 && *s >= 9))
		s++;
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

void	exit_(char *string, int error)
{
	if (error == 1)
    {
		printf("%s\n", string);
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

void    print_status(t_data data)
{
    printf("time to die %d\n", data.num_of_philos);
    printf("time_to_die %d\n", data.time_to_die);
    printf("time_to_eat %d\n", data.time_to_eat);
    printf("time_to_sleep %d\n", data.time_to_sleep);
    printf("n_necessity_to_eat %d\n", data.n_necessity_to_eat);
	printf("**************************\n");
}