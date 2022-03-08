/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:46 by jkosiara          #+#    #+#             */
/*   Updated: 2022/03/08 14:29:18 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <pthread.h>
// #include <sys/time.h>
#include "philosophers.h"

// typedef struct s_philo
// {
// 	int fork_l;
// 	int fork_r;
// 	int pos;
// }				t_philo;

// typedef struct s_info{
// 	int number_of_philosophers;
// 	int time_to_die;
// 	int time_to_eat;
// 	int time_to_sleep;
// 	t_philo		philo;
// }				t_info;

// pthread_mutex_t mutex;

// // int		ft_atoi(char *str)
// {
// 	int	i;
// 	int	sign;
// 	int	num;

// 	i = 0;
// 	sign = 1;
// 	num = 0;
// 	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
// 	|| (str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
// 		i++;
// 	if (str[i] == '-')
// 		sign = -1;
// 	if (str[i] == '-' || str[i] == '+')
// 		i++;
// 	while (str[i] >= '0' && str[i] <= '9')
// 		num = num * 10 + (str[i++] - '0');
// 	return (num * sign);
// }

// static void	ft_parsing(t_info *info, int argc, char *argv[])
// {
// 	info->number_of_philosophers = ft_atoi(argv[1]);
// 	info->time_to_die = ft_atoi(argv[2]);
// 	info->time_to_eat = ft_atoi(argv[3]);
// 	info->time_to_sleep = ft_atoi(argv[4]);
// }

// static int ft_check_arg(t_info *info, int argc)
// {
// 	if (argc <= 0)
// 		return(1);
// 	if (argc == 5 && 
// 		return (1);
// 	if (info->time_to_die <= 0)
// 		return (1);
// 	if (info->time_to_eat <=0)
// 		return (1);
// 	if (info->time_to_sleep <= 0)
// 		return (1);
// 	return(1);
// }

// void* routine(t_info *info)
// {
// 	philo->fork_l[1][info->philo] = 1;
// 	philo->fork_r[1][%info->philo + 1] = 1;	

// }

void	declare_philosophers(t_info *info)
{
	int i;

	i = 0;
	while(i < info->philo->number_of_philosophers)
	{
		if (pthread_mutex_lock(info->philo->fork_l))
			return i;
	}
}

static int ft_check_args(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (!ft_is_digit(argv[i]) || (!ft_atoi(argv[i])))
			return (1);
		i++;
	}
}

int	ft_init_philo(t_info *info)
{
	info->philo->mutex = malloc(sizeof(info->philo->mutex) *
		info->philo->number_of_philosophers);
	info->philo->forks = malloc(sizeof(info->philo->forks) *
		info->philo->number_of_philosophers);
	if (!info->philo->mutex || !info->philo->forks)
		return (0);
	memset(info->philo->forks, 0, info->philo->number_of_philosophers);
	ft_init_threads_mutexs(info);
	if (!ft_philos_launch(info))
		return (0);
	return (1);

}

int	init_philo(char **argv, t_info *info)
{
	if (ft_check_args(argv))
		return (1);
	info->philo->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->all_ate = 0;
	info->died = 0;
	if (info->philo->number_of_philosophers < 2 || info->time_to_die < 0 || 
		info->time_to_eat < 0 || info->time_to_sleep < 0 ||
		info->philo->number_of_philosophers > 250)
		return (1);
	if (argv[5])
	{
		info->meals = ft_atoi(argv[5]);
		if (info->meals <= 0)
			return (1);
	}
	else
		info->meals = -1;
	ft_init_philo(info);
}

int main(int argc, char **argv)
{
	t_info info;
	int ret;

	if (argc != 5 && argc != 6)
		return (ft_err(ERR_ARG));
	if (init_philo(argv, &info) == 1)
		return (ft_err(ERR_ARG_2));
	
	
}