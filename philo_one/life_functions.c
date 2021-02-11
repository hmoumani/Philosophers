/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:05:40 by hmoumani          #+#    #+#             */
/*   Updated: 2021/02/11 10:05:41 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void    status(t_philo *philo, int status)
{
    if (philo->status != DEAD)
        philo->status = status;
}

void    print_status(t_philo *philo)
{
    char *st;

    if (philo->status == EATING)
        st = "IS EATING";
    if (philo->status == SLEEPING)
        st = "IS SLEEPING";
    if (philo->status == THINKING)
        st = "IS THINKING";
    if (philo->status == DEAD)
        st = "IS DEAD x)";
    
    pthread_mutex_lock(&g_conf.mutex_output);
    printf("%d\t%s\t%ld\n", philo->id, st, (get_time_stamp() - g_time_start) / 
    1000);
    pthread_mutex_unlock(&g_conf.mutex_output);
}

void    think(t_philo *philo)
{
    status(philo, THINKING);

}