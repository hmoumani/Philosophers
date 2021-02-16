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

#include "philo_two.h"

int		ft_atoi(const char *str)
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
	g_conf.ti_to_die = ft_atoi(argv[2]) * 1000;
	g_conf.ti_to_eat = ft_atoi(argv[3]) * 1000;
	g_conf.ti_to_sleep = ft_atoi(argv[4]) * 1000;
	g_conf.nbr_to_end = -1;
	if (argc == 6)
		g_conf.nbr_to_end = ft_atoi(argv[5]);
	if (g_conf.nbr_philo < 0 || g_conf.ti_to_die < 0 ||
	g_conf.ti_to_eat < 0 || g_conf.ti_to_sleep < 0 ||
	(argc == 6 && g_conf.nbr_to_end < 0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*life_circle(void *param)
{
	t_philo *philo;

	philo = param;
	// pthread_mutex_lock(&g_conf.mutex);
    sem_wait(g_conf.mutex);
	while ((g_conf.nbr_to_end == -1 || philo->total_eated < g_conf.nbr_to_end)
	&& g_conf.run)
	{
		think(philo);
		forks(philo);
		eat(philo);
		leave_forks(philo);
		ft_sleep(philo);
	}
	status(philo, DONE);
	// pthread_mutex_unlock(&g_conf.mutex);
    sem_post(g_conf.mutex);
	return (NULL);
}

int		ft_init(void)
{
	int i;

	g_time_start = get_time_stamp();
	g_conf.run = TRUE;
	// if (!(g_forks = (pthread_mutex_t *)malloc(g_conf.nbr_philo *
	// sizeof(pthread_mutex_t))))
	// 	return (EXIT_FAILURE);
    g_sema = sem_open("forks", O_CREAT, 0660, g_conf.nbr_philo);
    g_conf.mutex_output = sem_open("output", O_CREAT, 0660, 1);
    g_conf.mutex = sem_open("global", O_CREAT, 0660, 1);
    if (g_sema == SEM_FAILED)
        return (EXIT_FAILURE);
    // sem_init(&g_sema, 0, g_conf.nbr_philo);
	// if (pthread_mutex_init(&g_conf.mutex, NULL) ||
	// pthread_mutex_init(&g_conf.mutex_output, NULL))
	// 	return (EXIT_FAILURE);
	i = 0;
	// while (i < g_conf.nbr_philo)
	// 	if (pthread_mutex_init(&g_forks[i++], NULL))
	// 		return (EXIT_FAILURE);
	if (!(g_philos = malloc(g_conf.nbr_philo * sizeof(t_philo))))
		return (EXIT_FAILURE);
	if (ft_init2())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
