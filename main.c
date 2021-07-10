/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 20:30:43 by fsarbout          #+#    #+#             */
/*   Updated: 2021/07/10 21:05:06 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *myturn()
{
    int i = 0;
    while (i < 10) 
    {
        sleep(1);
        printf ("my turn\n");
        i++;
    }
    return 0;
}

void    *yourturn()
{
    int i = 0;
    while (i < 3)
    {
        sleep(2);
        printf ("your turn\n");
        i++;
    }
    return 0;
}


int main()
{
    //this program work on more than thind concurrently
    
    pthread_t newthread;
    
    pthread_create(&newthread, 0 , myturn, 0);
    yourturn();
     
    //wait until the thread is done  before we exit
    pthread_join(newthread, NULL);
    
}