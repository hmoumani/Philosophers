/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:53:03 by hmoumani          #+#    #+#             */
/*   Updated: 2021/02/11 17:53:04 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_micro_s_t	get_time_stamp(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return (timev.tv_sec * (t_micro_s_t)1000000 + timev.tv_usec);
}

int			ft_init2(void)
{
	int i;

	i = 0;
	while (i < g_conf.nbr_philo)
	{
		g_philos[i].id = i + 1;
		g_philos[i].is_dead = FALSE;
		g_philos[i].status = THINKING;
		g_philos[i].time_last_eat = g_time_start;
		if (pthread_create(&g_philos[i].philo_t, NULL, &life_circle,
		&g_philos[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void		print_status(t_philo *philo)
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
	printf("%ld\t%d\t%s\n", (get_time_stamp() - g_time_start) /
	1000, philo->id, st);
	pthread_mutex_unlock(&g_conf.mutex_output);
}

void		status(t_philo *philo, int status)
{
	if (philo->status != DEAD)
		philo->status = status;
}

int			doctor(void)
{
	int done;
	int i;

	done = 0;
	while (done < g_conf.nbr_philo)
	{
		done = 0;
		i = 0;
		while (i < g_conf.nbr_philo)
		{
			if (g_philos[i].status == DONE)
				done++;
			else if ((get_time_stamp() - g_philos[i].time_last_eat >
			g_conf.ti_to_die)
			&& g_philos[i].status != EATING)
			{
				g_conf.run = FALSE;
				g_philos[i].status = DEAD;
				print_status(&g_philos[i]);
				return (EXIT_SUCCESS);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
