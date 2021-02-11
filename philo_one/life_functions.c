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

void	status(t_philo *philo, int status)
{
	if (philo->status != DEAD)
		philo->status = status;
}

void	print_status(t_philo *philo)
{
	char *st;

	st = NULL;
	if (philo->status == EATING)
		st = "is eating";
	else if (philo->status == SLEEPING)
		st = "is sleeping";
	else if (philo->status == THINKING)
		st = "is thinking";
	else if (philo->status == DEAD)
		st = "died";
	else if (philo->status == TAKING_FORKS)
		st = "has taken a fork";
	
	pthread_mutex_lock(&g_conf.mutex_output);
	printf("%ld\t%d\t%s\n",(get_time_stamp() - g_time_start) / 
	1000, philo->id, st);
	pthread_mutex_unlock(&g_conf.mutex_output);
}

void	think(t_philo *philo)
{
	status(philo, THINKING);
	print_status(philo);
	pthread_mutex_unlock(&g_conf.mutex);
	pthread_mutex_unlock(&g_forks[philo->id - 1]);
	pthread_mutex_unlock(&g_forks[philo->id % g_conf.nbr_philo]);
}

void	forks(t_philo *philo)
{
	pthread_mutex_unlock(&g_conf.mutex);
	status(philo, TAKING_FORKS);
	pthread_mutex_lock(&g_forks[philo->id - 1]);
	pthread_mutex_lock(&g_forks[philo->id % g_conf.nbr_philo]);
	print_status(philo);
}

void	eat(t_philo *philo)
{
	status(philo, EATING);
	print_status(philo);
	philo->total_eated++;
	philo->time_last_eat = get_time_stamp();
	usleep(g_conf.ti_to_eat - 15000);
    while (get_time_stamp() - philo->time_last_eat < g_conf.ti_to_eat)
        ;
}

void	leave_forks(t_philo *philo)
{
	status(philo, LEAVING_FORKS);
	pthread_mutex_unlock(&g_forks[philo->id - 1]);
	pthread_mutex_unlock(&g_forks[philo->id % g_conf.nbr_philo]);
}
void	ft_sleep(t_philo *philo)
{
    philo->start_sleep = get_time_stamp();
	status(philo, SLEEPING);
	print_status(philo);
    usleep(g_conf.ti_to_sleep - 15000);
    while (get_time_stamp() - philo->start_sleep < g_conf.ti_to_sleep)
        ;
}
