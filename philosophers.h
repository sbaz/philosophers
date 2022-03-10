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
#define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
#include <sys/time.h>

#define ERR_ARG		"Wrong number of philosophers"
#define ERR_ARG_2	"Wrong input"
#define ERR_INIT	"Error in initialization."


/* pthread_mutex_t è una struttura che contiene:
- Nome del mutex
- Proprietario
- Contatore
- Struttura associata al mutex
- La coda dei processi sospesi in attesa che mutex sia libero.
… e simili */

typedef struct s_philo{
	int number_of_philosophers;
	int fork_l;
	int fork_r;
	int mutex;
	int forks;
	pthread_mutex_t *mutex;

}				t_philo;

typedef struct s_info{
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	int all_ate;
	int died;
	int meals;
	t_philo	*philo;
}				t_info;

static void	ft_parsing(t_info *info, int argc, char *argv[]);
static int ft_check_arg(t_info *info, int argc);

#endif