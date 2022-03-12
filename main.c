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

int	init_philo2(t_info *info)
{
	int	i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_philosophers);
	if (!info->forks)
		return (1);
	while (i < info->number_of_philosophers)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (1);
		if (pthread_mutex_init(&info->philo[i].mutex, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&info->philo->output, NULL) != 0)
		return (1);
	return (0);
}
}

void	init_thinkeatsleep(t_info *info, char **argv)
{
	int i;

	i = 0;
	while(i < info->number_of_philosophers)
	{
		info->philo->time_to_die = ft_atoi(argv[2]);
		info->philo->time_to_eat = ft_atoi(argv[3]);
		info->philo->time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			info->philo[i].meals = ft_atoi(argv[5]);
		else
			info->philo[i].meals = -1;
//		info->philo[i].run_time = get_time();
		info->philo[i].starv_timer = get_time();
		info->philo[i].output = &info->philo->output;
		info->philo[i].left_fork = &info->forks[i];
		info->philo[i].right_fork = &info->forks[(i + 1) % info->number_of_philosophers];
		i++;
	}
	if (info->number_of_philosophers < 2 || info->philo->time_to_die < 0 || 
		info->philo->time_to_eat < 0 || info->philo->time_to_sleep < 0)
		return (1);
}

int	init_philo(char **argv, t_info *info)
{
	if (ft_check_args(argv))
		return (1);
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->philo = malloc(sizeof(t_philo) * info->number_of_philosophers);
	if(!info->philo)
		return (1);
	init_thinkeatsleep(info);
	info->philo->all_ate = 0;
	info->philo->died = 0;
	if (argv[5])
	{
		info->philo->meals = ft_atoi(argv[5]);
		if (info->philo->meals <= 0)
			return (1);
	}
	else
		info->philo->meals = -1;
	init_philo2(info);
}

int main(int argc, char **argv)
{
	t_info info;
	int ret;

	if (argc != 5 && argc != 6)
		return (ft_err(ERR_ARG));
	if (init_philo(argv, &info) == 1)
		return (ft_err(ERR_ARG_2));
	if (init_pthread(&info) == 1)
		ft_philo(&info);
	else
		return (ft_err(ERR_INIT));	
	return (0);
}