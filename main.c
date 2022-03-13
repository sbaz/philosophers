/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calzino <calzino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:46 by jkosiara          #+#    #+#             */
/*   Updated: 2022/03/13 07:59:59 by calzino          ###   ########.fr       */
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
	while (++i < info->nphilo)
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
	while (++i < info->nphilo)
		pthread_join(info->thread[i], NULL);
	pthread_mutex_destroy(philo.mutex);
	free(philo.mutex);
	return (0);
}

static int	set_forks(t_info *info, t_forks **forks)
{
	int	i;

	info->thread = (pthread_t *)malloc(info->nphilo * sizeof(pthread_t));
	*forks = (t_forks *)malloc(info->nphilo * sizeof(t_forks));
	if (!info->thread || !forks)
		return (1);
	i = -1;
	while (++i < info->nphilo)
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
	info->nphilo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	if (info->nphilo < 0 || info->t_die <= 0
		|| info->t_eat <= 0 || info->t_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		info->ndinner = ft_atoi(argv[5]);
		if (info->ndinner == 0)
			return (1);
	}
	else
		info->ndinner = 0;
	info->death = 0;
	info->deadlock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!info->deadlock)
		return (1);
	pthread_mutex_init(info->deadlock, NULL);
	if (set_forks(info, forks))
		return (1);
	return (0);
}

int	error(int error)
{
	if (error == 1)
		write(1, "Invalid arguments\n", 18);
	if (error == 2)
		write(1, "The info is not set\n", 21);
	if (error == 3)
		write(1, "Philosophers not created\n", 20);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_forks	*forks;

	if (argc != 5 && argc != 6)
		return (error(1));
	if (set_info(&info, &forks, argv, argc))
		return (error(2));
	if (info.nphilo == 0)
		return (0);
	if (init(&info, &forks))
		return (error(3));
	ft_free(&info, forks);
	return (0);
}
