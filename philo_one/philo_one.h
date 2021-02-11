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
# define False 0
# define True 1
# define EATING 2
# define THINKING 3
# define SLEEPING 4
# define DEAD 5
# define TAKING_FORKS 6
# define LEAVING_FORKS 7

typedef long	t_micro_s_t;

typedef struct		s_conf
{
	int				nbr_philo;
	int				run;
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
	int			total_eated;
	int			is_dead;
	pthread_t	philo_t;
	t_micro_s_t	time_last_eat;
}				t_philo;

t_micro_s_t		g_time_start;
t_conf			g_conf;
pthread_mutex_t *g_forks;
t_philo			*g_philos;

int			ft_error(char *error_message);
int			ft_collect_data(int argc, char **argv);
int			ft_atoi(const char *str);
int			ft_init();
void		think(t_philo *philo);
void		forks(t_philo *philo);
void		eat(t_philo *philo);
void		leave_forks(t_philo *philo);
t_micro_s_t	get_time_stamp(void);
void		print_status(t_philo *philo);

#endif
