/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:04:57 by aouichou          #+#    #+#             */
/*   Updated: 2022/11/21 19:24:18 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlock_forks(t_philo *philosopher)
{
	if (philosopher->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
	}
}

int	lock_forks(t_philo *philosopher)
{
	if (philosopher->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philosopher->left_fork);
		philosopher->stop = actions(philosopher, TAKE_FORK);
		if (philosopher->left_fork == philosopher->right_fork)
			return (1);
		pthread_mutex_lock(philosopher->right_fork);
		philosopher->stop = actions(philosopher, TAKE_FORK);
	}
	if (philosopher->philo_id % 2 != 0)
	{
		pthread_mutex_lock(philosopher->right_fork);
		philosopher->stop = actions(philosopher, TAKE_FORK);
		if (philosopher->left_fork == philosopher->right_fork)
			return (1);
		pthread_mutex_lock(philosopher->left_fork);
		philosopher->stop = actions(philosopher, TAKE_FORK);
	}
	return (0);
}

int	eating(t_philo *philosopher)
{
	int	ret;

	ret = 0;
	ret = lock_forks(philosopher);
	if (ret == 1)
	{
		pthread_mutex_unlock(philosopher->left_fork);
		return (ret);
	}
	philosopher->stop = actions(philosopher, EAT);
	ft_sleep(philosopher->ptr, philosopher->ptr->time_to_eat);
	unlock_forks(philosopher);
	return (ret);
}
