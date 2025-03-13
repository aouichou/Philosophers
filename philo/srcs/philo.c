/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:35:32 by aouichou          #+#    #+#             */
/*   Updated: 2022/12/12 18:32:28 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_death(t_main *ptr)
{
	int		i;
	time_t	time;

	while (1)
	{
		i = -1;
		pthread_mutex_lock(&(ptr->writing_mutex));
		time = get_time();
		while (++i < ptr->phils_nb)
		{
			if (time - ptr->philosophers[i].last_meal >= ptr->time_to_die)
			{
				print(&(ptr->philosophers[i]), "died");
				ptr->end = 1;
				break ;
			}
		}
		if (ptr->end == 1)
		{
			pthread_mutex_unlock(&(ptr->writing_mutex));
			return ;
		}
		pthread_mutex_unlock(&(ptr->writing_mutex));
		ft_sleep(ptr, 5);
	}
}

int	check_meal_nbr(t_main *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->phils_nb)
	{
		if (ptr->philosophers[i].meals < ptr->meal_amount)
			return (0);
		i++;
	}
	ptr->end = 1;
	return (1);
}

int	actions(t_philo *philosopher, int action)
{
	pthread_mutex_lock(&(philosopher->ptr->writing_mutex));
	if (philosopher->ptr->end == 1)
	{
		pthread_mutex_unlock(&(philosopher->ptr->writing_mutex));
		return (1);
	}
	if (action == EAT)
	{
		print(philosopher, "is eating");
		philosopher->last_meal = get_time();
	}
	else if (action == SLEEP)
	{
		print(philosopher, "is sleeping");
		philosopher->meals++;
		if (philosopher->meals == philosopher->ptr->meal_amount)
			check_meal_nbr(philosopher->ptr);
	}
	else if (action == THINK)
		print(philosopher, "is thinking");
	else if (action == TAKE_FORK)
		print(philosopher, "has taken a fork");
	pthread_mutex_unlock(&(philosopher->ptr->writing_mutex));
	return (0);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = ph;
	if (philo->philo_id % 2 == 0)
		ft_sleep(philo->ptr, philo->ptr->time_to_eat / 3);
	while (!(philo->stop))
	{
		philo->stop = actions(philo, THINK);
		if (philo->meals != 0)
			ft_sleep(philo->ptr, ((philo->ptr->time_to_die) * 9) / 10
				- (get_time() - philo->last_meal));
		philo->stop = eating(philo);
		if (philo->stop)
			break ;
		philo->stop = actions(philo, SLEEP);
		ft_sleep(philo->ptr, philo->ptr->time_to_sleep);
	}
	return (NULL);
}

int	creat_philosophers(t_main *ptr)
{
	int		i;

	i = 0;
	ptr->start_time = get_time();
	while (i < ptr->phils_nb)
	{
		ptr->philosophers[i].last_meal = get_time();
		if (pthread_create(&(ptr->philosophers[i].philosopher), NULL,
				&routine, &(ptr->philosophers[i])))
		{
			pthread_mutex_lock(&(ptr->writing_mutex));
			ft_error(ptr, "pthread create", 0, errno);
			ptr->end = 1;
			pthread_mutex_unlock(&(ptr->writing_mutex));
			return (EXIT_FAILURE);
		}
		i++;
	}
	check_death(ptr);
	return (EXIT_SUCCESS);
}
