/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calzino <calzino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:03:51 by eperaita          #+#    #+#             */
/*   Updated: 2022/03/13 07:59:59 by calzino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

static int	borrowed(t_philo *philo, int on)
{
	int	fork;

	if (philo->id == 1)
		fork = philo->info->nphilo - 1;
	else
		fork = philo->id - 2;
	if (philo->forks[fork].fork != on)
	{
		pthread_mutex_lock(&philo->forks[fork].mutex);
		philo->forks[fork].fork = on;
		if (on == 0)
			printf("%ld %d has taken a fork\n", o_clock(philo), philo->id);
		pthread_mutex_unlock(&philo->forks[fork].mutex);
		return (1);
	}
	return (0);
}

static int	get_fork_and_return(t_philo *philo, int on, int wait)
{
	while (wait == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1].mutex);
		if (philo->forks[philo->id - 1].fork != on)
		{
			philo->forks[philo->id - 1].fork = on;
			pthread_mutex_unlock(&philo->forks[philo->id - 1].mutex);
			if (on == 0)
				printf("%ld %d has taken a fork\n", o_clock(philo), philo->id);
			if (philo->info->nphilo != 1)
			{
				borrowed(philo, on);
				wait = 1;
			}
		}
		pthread_mutex_unlock(&philo->forks[philo->id - 1].mutex);
		if (any_dead(philo))
			return (1);
	}
	return (0);
}

int	thinking(t_philo *philo)
{
	if (philo->eated)
		printf("%ld %d is thinking\n", o_clock(philo), philo->id);
	if (philo->info->nphilo % 2 != 0)
	{
		if (my_uslip(philo, ((philo->info->t_eat * 2)
					- philo->info->t_sleep)))
			return (1);
	}
	else if (philo->info->nphilo % 2 == 0)
	{
		if (my_uslip(philo, (philo->info->t_eat - philo->info->t_sleep)))
			return (1);
	}
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (philo->eated)
		printf("%ld %d is sleeping\n", o_clock(philo), philo->id);
	if (my_uslip(philo, philo->info->t_sleep))
		return (1);
	return (0);
}

int	eating(t_philo *philo)
{
	if (get_fork_and_return(philo, 0, 0))
		return (1);
	gettimeofday(&philo->eatime, NULL);
	printf("%ld %d is eating\n", o_clock(philo), philo->id);
	if (my_uslip(philo, philo->info->t_eat))
		return (1);
	get_fork_and_return(philo, 1, 0);
	return (0);
}
