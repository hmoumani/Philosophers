/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:08:05 by hmoumani          #+#    #+#             */
/*   Updated: 2021/02/05 12:08:07 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		integer;

	i = 0;
	integer = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = (str[i] == 45 ? -1 : 1);
	if (str[i] == 43 || str[i] == 45)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			if ((unsigned long)integer * 10 > 9223372036854775807)
				return (sign == 1) ? -1 : 0;
			integer *= 10;
			integer += str[i] - 48;
		}
		else
			return (integer * sign);
		i++;
	}
	return (integer * sign);
}

int		ft_error(char *error_message)
{
	printf("%s\n", error_message);
	return (EXIT_FAILURE);
}

int		ft_collect_data(int argc, char **argv)
{
	g_conf.nbr_philo = ft_atoi(argv[1]);
	g_conf.ti_to_die = ft_atoi(argv[2]);
	g_conf.ti_to_eat = ft_atoi(argv[3]);
	g_conf.ti_to_sleep = ft_atoi(argv[4]);
	g_conf.nbr_to_end = -1;
	if (argc == 6)
		g_conf.nbr_to_end = ft_atoi(argv[5]);
	if (g_conf.nbr_philo < 0 || g_conf.ti_to_die < 0 || 
	g_conf.ti_to_eat < 0 || g_conf.ti_to_sleep < 0 ||
	(argc == 6 && g_conf.nbr_to_end < 0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_init()
{
	forks = (pthread_mutex_t *)malloc(g_conf.nbr_philo * sizeof(pthread_mutex_t));
}