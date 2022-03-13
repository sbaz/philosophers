/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calzino <calzino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:16:20 by pceccoli          #+#    #+#             */
/*   Updated: 2022/03/13 07:14:15 by calzino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	borrowed(t_philo *philo, int on)
{
	int	fork;

	if (philo->id == 1)
		fork = philo->info->number_of_philosophers - 1;
	else
		fork = philo->id - 2;
	if (philo->forks[fork].fork != on)
	{
		pthread_mutex_lock(&philo->forks[fork].mutex);
		philo->forks[fork].fork = on;
		if (on == 0)
			printf("%ld %d %s", o_clock(philo), philo->id, TAKE_FRK);
		pthread_mutex_unlock(&philo->forks[fork].mutex);
		return (1);
	}
	return (0);
}

int	get_fork_and_return(t_philo *philo, int on, int wait)
{
	while (wait == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1].mutex);
		if (philo->forks[philo->id - 1].fork != on)
		{
			philo->forks[philo->id - 1].fork = on;
			pthread_mutex_unlock(&philo->forks[philo->id - 1].mutex);
			if (on == 0)
				printf("%ld %d %s", o_clock(philo), philo->id, TAKE_FRK);
			if (philo->info->number_of_philosophers != 1)
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
		printf("%ld %d %s", o_clock(philo), philo->id, THINKING);
	if (philo->info->number_of_philosophers % 2 != 0)
	{
		if (my_uslip(philo, ((philo->info->time_to_eat * 2)
					- philo->info->time_to_sleep)))
			return (1);
	}
	else if (philo->info->number_of_philosophers % 2 == 0)
	{
		if (my_uslip(philo, (philo->info->time_to_eat - philo->info->time_to_sleep)))
			return (1);
	}
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (philo->eated)
		printf("%ld %d %s", o_clock(philo), philo->id, SLEEP);
	if (my_uslip(philo, philo->info->time_to_sleep))
		return (1);
	return (0);
}

int	eating(t_philo *philo)
{
	if (get_fork_and_return(philo, 0, 0))
		return (1);
	gettimeofday(&philo->eatime, NULL);
	printf("%ld %d %s", o_clock(philo), philo->id, EATING);
	if (my_uslip(philo, philo->info->time_to_eat))
		return (1);
	get_fork_and_return(philo, 1, 0);
	return (0);
}