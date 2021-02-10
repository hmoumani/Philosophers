/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:03:27 by hmoumani          #+#    #+#             */
/*   Updated: 2021/02/05 12:03:28 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE
# define PHILO_ONE
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>

typedef long	t_micro_s_t;

typedef struct		s_conf
{
    int				nbr_philo;
    t_micro_s_t		ti_to_die;
    t_micro_s_t		ti_to_eat;
    t_micro_s_t		ti_to_sleep;
    int				nbr_to_end;
    pthread_mutex_t	mutex;
    pthread_mutex_t	mutex_output;
}					t_conf;

typedef struct	s_philo
{
    int			status;
	int			id;
	int			is_dead;
}				t_philo;


t_conf			g_conf;
pthread_mutex_t *g_forks;
pthread_t		*g_philos;

int		ft_error(char *error_message);
int     ft_collect_data(int argc, char **argv);
int		ft_atoi(const char *str);
int		ft_init();

#endif
