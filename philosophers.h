/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:14:57 by jkosiara          #+#    #+#             */
/*   Updated: 2022/03/08 12:35:37 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
#include <sys/time.h>

#define ERR_ARG		"Wrong number of philosophers"
#define ERR_ARG_2	"Wrong input"
#define ERR_INIT	"Error in initialization."

#define FORK_L  "takes left fork"
#define FORK_R  "takes right fork"
#define EAT     "eating"
#define SLEEP   "sleeping"
#define THINK   "thinking"
#define EAT_ALL "all philosophers ate"
#define DIE	 	"died"


/* pthread_mutex_t è una struttura che contiene:
- Nome del mutex
- Proprietario
- Contatore
- Struttura associata al mutex
- La coda dei processi sospesi in attesa che mutex sia libero.
… e simili */

typedef struct s_philo{
	int forks;
	int number_of_times_each_philosopher_must_eat;
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	int all_ate;
	int died;
	int meals;
	long long		starv_timer;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*output;
	pthread_mutex_t	*timer;
	pthread_mutex_t *mutex;

}				t_philo;

typedef struct s_info{
	int number_of_philosophers;
	pthread_mutex_t	*forks;
	t_philo	*philo;
}				t_info;


static int ft_check_arg(t_info *info, int argc);

#endif