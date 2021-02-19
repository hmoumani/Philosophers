/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:03:21 by hmoumani          #+#    #+#             */
/*   Updated: 2021/02/05 12:03:22 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr(int n)
{
	unsigned int result;

	result = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		result = -((unsigned int)n);
	}
	else
		result = n;
	if (result < 10)
		ft_putchar_fd(result + 48, 1);
	else
	{
		ft_putnbr(result / 10);
		ft_putchar_fd((result % 10) + 48, 1);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	if (s)
	{
		i = 0;
		while (s[i] != '\0')
		{
			write(fd, &s[i++], 1);
		}
	}
}

int		hold_prog(void)
{
	int	i;
	int j;
	int	status;

	i = 0;
	while (i < g_conf.nbr_philo)
	{
		waitpid(g_philos[i].pid, &status, 0);
		if (WEXITSTATUS(status) == 2)
		{
			j = 0;
			while (j < g_conf.nbr_philo)
				kill(g_philos[j++].pid, SIGKILL);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_error("usage ./philo_one number_of_philosophers time_to_die\
		time__eat time_to_slep [number_of_times_each_philsopher_must_eat]\n"));
	sem_unlink("forks");
	sem_unlink("output");
	sem_unlink("global");
	if (ft_collect_data(argc, argv))
		return (ft_error("error: arguments\n"));
	if (ft_init() || !hold_prog())
	{
		sem_unlink("forks");
		sem_unlink("output");
		sem_unlink("global");
		return (EXIT_SUCCESS);
	}
}
