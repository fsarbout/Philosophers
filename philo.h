/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 20:27:38 by fsarbout          #+#    #+#             */
/*   Updated: 2021/07/12 12:22:38 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
# include <sys/time.h>
# include <string.h>


# define TO_MICRO_S 1000




typedef struct s_data
{
    int num_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int n_necessity_to_eat;
    pthread_t th;
    //data type : ID of a thread . return by pthread_create
}       t_data;

// typedef struct s_philos
// {
//     t_data  data;
//     int     id;
//     int     is_dead;
//     int     last_eat;    
// }   t_philos;

int	    ft_atoi(const char *s);
void	exit_(char *string, int error);
void    print_status(t_data data);
int     is_pair(int i);

void    *routine(void *);

#endif