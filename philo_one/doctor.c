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

void	doctor()
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
			if (g_philos[i].total_eated > g_conf.nbr_to_end && g_conf.nbr_to_end > 0)
				done++;
			if (get_time_stamp() - g_philos[i].time_last_eat > g_conf.ti_to_die 
			&& g_philos[i].status != EATING)
			{
				g_conf.run = False;
				g_philos[i].status = DEAD;
				print_status(&g_philos[i]);
				return ;
			}
			i++;
		}
	}
}