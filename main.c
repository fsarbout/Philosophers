/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 20:30:43 by fsarbout          #+#    #+#             */
/*   Updated: 2021/07/12 15:07:16 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine(void *arg)
{
    int s = (int )arg;

    printf("first thread %d \n", s);
    return 0;    
}

void    *routine2(void *arg)
{
    int s = (int )arg;

    printf("second thread %d \n", s);
    return 0;    
}

void    *routine3(void *arg)
{
    int s = (int )arg;

    printf("third thread %d \n", s);
    return 0;    
}

void    *routine4(void *arg)
{
    int s = (int )arg;

    printf("fourth thread %d \n", s);
    return 0;    
}

void    *thread(void *arg)
{
    

}


int main(int ac, char **av)
{
    t_data data;
    t_philos *philo ;


    /* fill data */
    if (ac != 5 && ac != 6)
        exit_("Error : number of arguments", 1);
        
    // data = (t_data){ft_atoi(av[1]), ft_atoi(av[2]) * TO_MICRO_S
    //     , ft_atoi(av[3] )* TO_MICRO_S, ft_atoi(av[4])* TO_MICRO_S, 0,0};
    
    fill_data();
    if (ac == 6)
        data.n_necessity_to_eat = ft_atoi(av[5]) * TO_MICRO_S;  
    int philo_n = data.num_of_philos;
    while (philo_n--)
    {    
        pthread_create(&data.th, NULL, &routine, &philo[philo_n]);
        pthread_join(data.th, NULL);
    }
    
    printf ("hello\n");
    
    
    print_status(data);
}

