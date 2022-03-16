/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 07:40:30 by calzino           #+#    #+#             */
/*   Updated: 2022/03/16 23:48:08 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

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
	struct timeval	start;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				death;
	int				meals;
	pthread_mutex_t	*deadlock;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				group;
	struct timeval	lunch;
	int				eated;
	t_info			*info;
	t_forks			*forks;
	pthread_mutex_t	*mutex;
}	t_philo;

int			arg_check(int argc, char **argv);
void		*ft_routine(void *philo);
int			ft_perror(char *str);
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
