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

#include "philo_one.h"

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
		// write(1, "\n", 1);
	}
}

int	ft_strlen(char *s)
{
	int i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_error("usage ./philo_one number_of_philosophers time_to_die\
		time__eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"));
	if (ft_collect_data(argc, argv))
		return (EXIT_FAILURE);
	if (ft_init() || doctor())
		return (EXIT_SUCCESS);
}
