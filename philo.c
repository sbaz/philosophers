/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:40:00 by pceccoli          #+#    #+#             */
/*   Updated: 2022/03/16 22:40:51 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philos_routine(t_philo *philo)
{
	while (!any_dead(philo))
	{
		if (philo->group == 2)
		{
			philo->group = 3;
			if (sleeping(philo))
				break ;
		}
		if (philo->group == 3)
		{
			philo->group = 1;
			if (thinking(philo))
				break ;
		}
		if (philo->group == 1)
		{
			philo->group = 2;
			if (eating(philo))
				break ;
			philo->eated++;
			if (philo->info->meals
				&& (philo-> eated == philo->info->meals))
				break ;
		}
	}
}

static int	my_group(t_philo *philo)
{
	int	group;

	group = 0;
	if (philo->info->num_philo % 2 != 0 && philo->id == philo->info->num_philo)
		group = 3;
	else if (philo->id % 2 != 0)
		group = 1;
	else if (philo->id % 2 == 0)
		group = 2;
	return (group);
}

void	*ft_routine(void *philo)
{
	t_philo	copy;

	copy = *(t_philo *)philo;
	pthread_mutex_unlock(copy.mutex);
	copy.eated = 0;
	while (!copy.info->start.tv_sec
		&& !copy.info->start.tv_usec)
		usleep(10);
	copy.lunch = copy.info->start;
	copy.group = my_group(&copy);
	philos_routine(&copy);
	return (NULL);
}
