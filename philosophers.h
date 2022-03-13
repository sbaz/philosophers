/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calzino <calzino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 07:40:30 by calzino           #+#    #+#             */
/*   Updated: 2022/03/13 07:59:59 by calzino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define ERR_ARG1 "Wrong number of arguments"
# define ERR_ARG2 "Error in variable initialization"
# define ERR_INIT "Error initializing simulation"

typedef struct s_forks
{
	int				fork;
	pthread_mutex_t	mutex;
}	t_forks;

typedef struct s_info
{
	pthread_t		*thread;
	struct timeval	startime;
	int				nphilo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				death;
	int				ndinner;
	pthread_mutex_t	*deadlock;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				group;
	struct timeval	eatime;
	int				eated;
	t_info			*info;
	t_forks			*forks;
	pthread_mutex_t	*mutex;
}	t_philo;

void		*philos_dictator(void *philo);
int			is_dead(t_philo *philo);
int			any_dead(t_philo *philo);
long int	o_clock(t_philo *philo);
int			my_uslip(t_philo *philo, int time);
int			eating(t_philo *philo);
int			sleeping(t_philo *philo);
int			thinking(t_philo *philo);
int			ft_atoi(const char *str);
void		ft_free(t_info *info, t_forks *forks);
#endif
