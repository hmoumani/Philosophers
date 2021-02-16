/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:03:21 by hmoumani          #+#    #+#             */
/*   Updated: 2021/02/05 12:03:22 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_error("usage ./philo_one number_of_philosophers time_to_die\
		time__eat time_to_sleep [number_of_times_each_philosopher_must_eat]"));
    sem_close(g_sema);
    sem_unlink("forks");
	if (ft_collect_data(argc, argv))
		return (EXIT_FAILURE);
	if (ft_init() || doctor())
	{
		sem_close(g_sema);
        sem_unlink("forks");
		return (EXIT_SUCCESS);
	}
}
