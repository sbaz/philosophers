/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:46 by jkosiara          #+#    #+#             */
/*   Updated: 2022/03/16 21:50:06 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "philosophers.h"

static int	init(t_info *info, t_forks **forks)
{
	t_philo	philo;
	int		i;

	philo.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo.mutex)
		return (1);
	pthread_mutex_init(philo.mutex, NULL);
	i = -1;
	while (++i < info->num_philo)
	{
		pthread_mutex_lock(philo.mutex);
		philo.info = info;
		philo.forks = *forks;
		philo.id = i + 1;
		if (pthread_create(&info->thread[i]
				, NULL, &philos_dictator, &philo) != 0)
			return (1);
	}
	gettimeofday(&info->startime, NULL);
	i = -1;
	while (++i < info->num_philo)
		pthread_join(info->thread[i], NULL);
	pthread_mutex_destroy(philo.mutex);
	free(philo.mutex);
	return (0);
}

static int	set_forks(t_info *info, t_forks **forks)
{
	int	i;

	info->thread = (pthread_t *)malloc(info->num_philo * sizeof(pthread_t));
	*forks = (t_forks *)malloc(info->num_philo * sizeof(t_forks));
	if (!info->thread || !forks)
		return (1);
	i = -1;
	while (++i < info->num_philo)
	{
		(*forks + i)->fork = 1;
		if (pthread_mutex_init(&(*forks + i)->mutex, NULL))
			return (1);
	}
	return (0);
}

static int	set_info(t_info *info, t_forks **forks, char **argv, int argc)
{
	info->startime.tv_sec = 0;
	info->startime.tv_usec = 0;
	info->num_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->num_philo < 0 || info->time_to_die <= 0
		|| info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		info->meals = ft_atoi(argv[5]);
		if (info->meals == 0)
			return (1);
	}
	else
		info->meals = 0;
	info->death = 0;
	info->deadlock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!info->deadlock)
		return (1);
	pthread_mutex_init(info->deadlock, NULL);
	if (set_forks(info, forks))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_forks	*forks;

	if (argc != 5 && argc != 6)
		return (ft_perror(ERR_ARG1));
	if (set_info(&info, &forks, argv, argc))
		return (ft_perror(ERR_ARG2));
	if (info.num_philo == 0)
		return (0);
	if (init(&info, &forks))
		return (ft_perror(ERR_INIT));
	ft_free(&info, forks);
	return (0);
}
