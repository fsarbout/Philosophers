/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 20:27:38 by fsarbout          #+#    #+#             */
/*   Updated: 2022/02/09 00:20:18 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

# define TO_MICRO_S 1000

# define DEFAULT "\033[0m"
# define GREEN "\e[1;32m"
# define RED "\e[1;31m"
# define WHITE "\e[1;37m"
# define YELLOW "\e[1;33m"
# define BLUE "\e[1;34m"
# define PURPLE "\033[1;35m"

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_necessity_to_eat;
	int				num_forks;
	long			start_time;
	pthread_t		*th;
	pthread_mutex_t	*f_mutex;
	pthread_mutex_t	*e_mutex;
	pthread_mutex_t	o_mutex;
	pthread_mutex_t	dead_mutex;
}					t_data;

typedef struct s_philos
{
	t_data	*data;
	int		id;
	long	last_eat;
	int		has_forks;
	int		is_dead;
	int		eat_nb;
}			t_philos;

int		ft_atoi(const char *s);
int		exit_(void);
int		is_pair(int i);
int		collect_data(char **av, int ac, t_data *data);
void	start_simi(t_philos *philo, t_data *data);
void	mutex_init(t_data *data);
void	print_status(char *status, char *color, t_philos *ph);
void	take_forks(t_philos *ph);
void	eating(t_philos *ph);
void	thinking(t_philos *ph);
void	sleeping(t_philos *ph);
void	*routine(void *arg);
long	get_time(void);
void	ft_free(t_philos *philo);
int		check_death(t_philos *philo, t_data *data);
void	u_sleep(int usec);
int		check_nb_eat(t_philos *philo);
void	thinking(t_philos *ph);

#endif
