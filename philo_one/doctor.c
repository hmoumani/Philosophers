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

int		doctor()
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
			else if ((get_time_stamp() - g_philos[i].time_last_eat > g_conf.ti_to_die)
			&& g_philos[i].status != EATING)
			{
				g_conf.run = False;
				g_philos[i].status = DEAD;
				print_status(&g_philos[i]);
				pthread_mutex_lock(&g_conf.mutex_output);
				return (EXIT_SUCCESS);
			}
			i++;
		}
	}
	pthread_mutex_lock(&g_conf.mutex_output);
	return (EXIT_SUCCESS);
}