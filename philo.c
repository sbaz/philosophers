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

static int	ft_turn(t_philo *philo)
{
	int	group;

	group = 0;
	if (philo->info->number_of_philosophers % 2 != 0 && philo->id ==
		philo->info->number_of_philosophers)
		group = 3;
	else if (philo->id % 2 != 0)
		group = 1;
	else if (philo->id % 2 == 0)
		group = 2;
	return (group);
}

void	*routine(void *philo)
{
	t_philo	philo_r;

	philo_r = *(t_philo *)philo;
	pthread_mutex_unlock(philo_r.mutex);
	philo_r.eated = 0;
	while (!philo_r.info->startime.tv_sec
		&& !philo_r.info->startime.tv_usec)
		usleep(10);
	philo_r.eatime = philo_r.info->startime;
	philo_r.group = ft_turn(&philo_r);
	philos_routine(&philo_r);
	return (NULL);
}