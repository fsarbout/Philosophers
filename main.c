/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 20:30:43 by fsarbout          #+#    #+#             */
/*   Updated: 2021/07/12 12:29:41 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine(void *arg)
{
    int *s = (int *)arg;
    printf("l***** %d \n", *s);
    return 0;    
}


int main(int ac, char **av)
{
    t_data data;


    /* fill data */
    if (ac != 5 && ac != 6)
        exit_("Error : number of arguments", 1);
    data = (t_data){ft_atoi(av[1]), ft_atoi(av[2]) * TO_MICRO_S
        , ft_atoi(av[3] )* TO_MICRO_S, ft_atoi(av[4])* TO_MICRO_S, 0,};
    if (ac == 6)
        data.n_necessity_to_eat = ft_atoi(av[5]) * TO_MICRO_S;  
    
    pthread_create(&data.th, NULL, routine, data.th);
    
    printf ("hello\n");
    
    
    print_status(data);
}

