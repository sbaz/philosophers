/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calzino <calzino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:28:38 by eperaita          #+#    #+#             */
/*   Updated: 2022/03/13 07:59:59 by calzino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

/////////////////////////DEADS///////////////////

int	is_dead(t_philo *philo)
{
	struct timeval	now;
	long int		period;

	gettimeofday(&now, NULL);
	period = (now.tv_sec * 1000 + now.tv_usec / 1000)
		- (philo->eatime.tv_sec * 1000 + philo->eatime.tv_usec / 1000);
	if (period > philo->info->t_die)
		return (1);
	return (0);
}

int	any_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->info->deadlock);
	if (philo->info->death)
	{
		pthread_mutex_unlock(philo->info->deadlock);
		return (1);
	}
	if (is_dead(philo))
	{
		philo->info->death = 1;
		pthread_mutex_unlock(philo->info->deadlock);
		printf("%ld %d died\n", o_clock(philo), philo->id);
		return (1);
	}
	pthread_mutex_unlock(philo->info->deadlock);
	return (0);
}

////////////////// TIMESTAMP //////////////////

long int	o_clock(t_philo *philo)
{
	struct timeval	now;
	long int		ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec * 1000 + now.tv_usec / 1000)
		- (philo->info->startime.tv_sec * 1000
			+ philo->info->startime.tv_usec / 1000);
	return (ms);
}

//////////////////MY USLIP //////////////////////////

int	my_uslip(t_philo *philo, int time)
{
	struct timeval	now;
	struct timeval	end;
	int				i;

	gettimeofday(&now, NULL);
	gettimeofday(&end, NULL);
	i = 0;
	while ((end.tv_sec * 1000 + end.tv_usec / 1000)
		- (now.tv_sec * 1000 + now.tv_usec / 1000) < time)
	{
		usleep(100);
		gettimeofday(&end, NULL);
		if ((end.tv_sec * 1000 + end.tv_usec / 1000)
			- (now.tv_sec * 1000 + now.tv_usec / 1000) - i > 10)
		{
			i += 10;
			if (any_dead(philo))
				return (1);
		}
	}
	if (any_dead(philo))
		return (1);
	return (0);
}
