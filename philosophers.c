/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:46 by jkosiara          #+#    #+#             */
/*   Updated: 2021/10/21 18:45:53 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int fork_l;
	int fork_r;
	int pos;
}				t_philo;

typedef struct s_info{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	t_philo		philo;
}				t_info;



pthread_mutex_t mutex;

int		ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
	|| (str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num * sign);
}

static void	ft_parsing(t_info *info, int argc, char *argv[])
{
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
}

static int ft_check_arg(t_info *info, int argc)
{
	if (argc <= 0)
		return(1);
	if (argc == 5 && info->number_of_philosophers <= 0)
		return (1);
	if (info->time_to_die <= 0)
		return (1);
	if (info->time_to_eat <=0)
		return (1);
	if (info->time_to_sleep <= 0)
		return (1);
	return(1);
}

void* routine()
{
	info->forks[1][info->philo1] = 1;
	info->forks[1][%info->philo1 + 1] = 1;

}

void	declare_philosophers(t_info *info)
{
	int i;

	i = 0;
	while(i < info->number_of_philosophers)
	{
		if (pthread_mutex_lock(info->philo.fork_l))
			return l;
	{

	}
}

int main(int argc, char *argv[])
{
	t_info info;

	pthread_mutex_t mutex;
	pthread_t		philo1, philo2;

	int i = 0;
	while(i<= info.number_of_philosophers)
	{
		info.forks[i][0] = i;
		i++;
	}
	ft_parsing(&info, argc, argv);
	if (!ft_check_arg(&info,argc) == 1);
	{
		printf("%d\n",info.number_of_philosophers);
		printf("%d\n",info.time_to_die);
		printf("%d\n",info.time_to_eat);
		printf("%d\n",info.time_to_sleep);
	}

	pthread_create(philo1, NULL, &)
	if(pthread_mutex_init(&mutex, NULL))
	}





	

	return 0;
}