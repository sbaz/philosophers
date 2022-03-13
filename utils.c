/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calzino <calzino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 07:14:44 by calzino           #+#    #+#             */
/*   Updated: 2022/03/13 07:14:46 by calzino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	unsigned int		i;
	int					neg;
	unsigned long int	nb;

	i = 0;
	neg = 1;
	nb = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - 48);
	return (nb * neg);
}

void	ft_free(t_info *info, t_forks *forks)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philosophers)
		pthread_mutex_destroy(&forks[i].mutex);
	free(forks);
	free(info->thread);
	pthread_mutex_destroy(info->deadlock);
	free(info->deadlock);
}
