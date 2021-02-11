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

t_micro_s_t	get_time_stamp(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return (timev.tv_sec * (t_micro_s_t)1000000 + timev.tv_usec);
}

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

void	*life_circle(void   *param)
{
    t_philo *philo;

    philo = param;
	pthread_mutex_lock(&g_conf.mutex);
	// printf("hello\n");
    while ((g_conf.nbr_to_end == -1 || philo->total_eated < g_conf.nbr_to_end)
    && g_conf.run)
    {
        think(philo);
        forks(philo);
		eat(philo);
        leave_forks(philo);
    }
	pthread_mutex_unlock(&g_conf.mutex);
    return (NULL);
}

int	ft_init()
{
	int i;

	g_time_start = get_time_stamp();
    g_conf.run = True;
	if (!(g_forks = (pthread_mutex_t *)malloc(g_conf.nbr_philo *
	sizeof(pthread_mutex_t))))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&g_conf.mutex, NULL) ||
	pthread_mutex_init(&g_conf.mutex_output, NULL))
		return (EXIT_FAILURE);
	i = 0;
	while (i < g_conf.nbr_philo)
		if (pthread_mutex_init(&g_forks[i++], NULL))
			return (EXIT_FAILURE);
	if (!(g_philos = malloc(g_conf.nbr_philo * sizeof(t_philo))))
		return (EXIT_FAILURE);
	// i = 0;
	// while (i < g_conf.nbr_philo)
	// 	pthread_join(g_philos[i++].philo_t, NULL);
    i = 0;
	printf("%d\n", g_conf.nbr_philo);
    while (i < g_conf.nbr_philo)
    {
        g_philos[i].id = i + 1;
        g_philos[i].is_dead = False;
        g_philos[i].status = THINKING;
        g_philos[i].time_last_eat = get_time_stamp();
		if (pthread_create(&g_philos[i].philo_t, NULL, &life_circle,
		&g_philos[i]))
			return (EXIT_FAILURE);
        i++;
    }
	i = 0;
	while (i < g_conf.nbr_philo)
	{
		pthread_join(g_philos[i++].philo_t, NULL);
	}
	return (EXIT_SUCCESS);
}
