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

#include "philo_two.h"

void	think(t_philo *philo)
{
	status(philo, THINKING);
	print_status(philo);
}

void	forks(t_philo *philo)
{
	// pthread_mutex_unlock(&g_conf.mutex);
    sem_post(g_conf.mutex);
	// pthread_mutex_lock(&g_forks[philo->id - 1]);
	// pthread_mutex_lock(&g_forks[philo->id % g_conf.nbr_philo]);
    sem_wait(g_sema);
    sem_wait(g_sema);
	status(philo, TAKING_FORKS);
	print_status(philo);
}

void	eat(t_philo *philo)
{
	status(philo, EATING);
	print_status(philo);
	philo->total_eated++;
	philo->time_last_eat = get_time_stamp();
	usleep(g_conf.ti_to_eat - 20000);
	while (get_time_stamp() - philo->time_last_eat < g_conf.ti_to_eat)
		;
}

void	leave_forks(t_philo *philo)
{
	status(philo, LEAVING_FORKS);
	// pthread_mutex_unlock(&g_forks[philo->id - 1]);
	// pthread_mutex_unlock(&g_forks[philo->id % g_conf.nbr_philo]);
    sem_post(g_sema);
    sem_post(g_sema);
}

void	ft_sleep(t_philo *philo)
{
	philo->start_sleep = get_time_stamp();
	status(philo, SLEEPING);
	print_status(philo);
	usleep(g_conf.ti_to_sleep - 20000);
	while (get_time_stamp() - philo->start_sleep < g_conf.ti_to_sleep)
		;
}
