/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:05:40 by hmoumani          #+#    #+#             */
/*   Updated: 2021/02/11 10:05:41 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void    status(t_philo *philo, int status)
{
    if (philo->status != DEAD)
        philo->status = status;
}

void    think(t_philo *philo)
{
    philo->status = 
}