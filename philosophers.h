
#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

# define ERR_ARG	"Wrong Number of Arguments"
# define ERR_ARG2	"Error Setting Variables of Simulation"
# define ERR_INIT	"Error Initializing Philosophers"

# define TAKE_FRK	"has taken a fork\n"
# define THINKING	"is thinking\n"
# define DIED		"died\n"
# define SLEEP		"is sleeping\n"
# define EATING		"is eating\n"

typedef struct s_forks
{
	int				fork;
	pthread_mutex_t	mutex;
}	t_forks;

typedef struct s_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				death;
	struct timeval	startime;
	pthread_t		*thread;
	pthread_mutex_t	*deadlock;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				group;
	int				eated;
	struct timeval	eatime;
	t_info			*info;
	t_forks			*forks;
	pthread_mutex_t	*mutex;
}	t_philo;

void		*routine(void *philo);
int			is_dead(t_philo *philo);
int			any_dead(t_philo *philo);
long int	o_clock(t_philo *philo);
int			my_uslip(t_philo *philo, int time);
int			eating(t_philo *philo);
int			sleeping(t_philo *philo);
int			thinking(t_philo *philo);
int			ft_perror_philo(char *str);
int			ft_atoi(const char *str);
void		ft_free(t_info *info, t_forks *forks);
#endif