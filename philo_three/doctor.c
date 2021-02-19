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

#include "philo_three.h"

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
	g_conf.stop_write = FALSE;
	while (i < g_conf.nbr_philo)
	{
		g_philos[i].id = i + 1;
		g_philos[i].is_dead = FALSE;
		g_philos[i].status = THINKING;
		g_philos[i].total_eated = 0;
		g_philos[i].time_last_eat = g_time_start;
		// if (pthread_create(&g_philos[i].philo_t, NULL, &life_circle,
		// &g_philos[i]))
		if ((g_philos[i].pid = fork()) == 0)
			life_circle(&g_philos[i]);
		else if (g_philos[i].pid < 0)
			return (ft_error("error: fatal\n"));
		i++;
	}
	return (EXIT_SUCCESS);
}

void		print_status(t_philo *philo)
{
	char *st;

	if (!g_conf.run)
		return ;
	st = NULL;
	if (philo->status == EATING)
		st = "is eating\n";
	else if (philo->status == SLEEPING)
		st = "is sleeping\n";
	else if (philo->status == THINKING)
		st = "is thinking\n";
	else if (philo->status == DEAD)
		st = "died\n";
	else if (philo->status == TAKING_FORKS)
		st = "has taken a fork\n";
    sem_wait(g_conf.sem_output);
	ft_putnbr((get_time_stamp() - g_time_start) /
	1000);
	write(1, " ", 1);
	ft_putnbr(philo->id);
	write(1, " ", 1);
	ft_putstr_fd(st, 1);
	sem_post(g_conf.sem_output);
}

void		status(t_philo *philo, int status)
{
	if (philo->status != DEAD)
		philo->status = status;
}

void		*doctor(void *param)
{
	t_philo		*philo;

	philo = param;
	while (philo->status != DONE)
	{
		if ((philo->status != EATING &&
		get_time_stamp() - philo->time_last_eat > g_conf.ti_to_die) ||
		philo->is_dead)
		{
			philo->status = DEAD;
			print_status(philo);
			g_conf.run = FALSE;
			exit(2);
		}
	}
	return (NULL);
}
