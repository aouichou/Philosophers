/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:55:19 by aouichou          #+#    #+#             */
/*   Updated: 2022/12/12 18:30:35 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*check_death(void *tmp)
{
	t_main	*ptr;

	ptr = tmp;
	while (1)
	{
		sem_wait(ptr->philosopher.rights);
		if (get_time() - ptr->philosopher.last_meal >= ptr->time_to_die)
		{
			sem_wait(ptr->writing_sem);
			print(ptr, &ptr->philosopher, "died");
			sem_post(ptr->end);
			sem_post(ptr->philosopher.rights);
			exit(0);
		}
		sem_post(ptr->philosopher.rights);
		ft_sleep(ptr, 1);
	}
	return (NULL);
}

void	*check_repletion(void *tmp)
{
	t_main	*ptr;
	int		i;

	ptr = tmp;
	i = 0;
	sem_wait(ptr->writing_sem);
	while (i < ptr->phils_nb)
	{
		sem_post(ptr->writing_sem);
		sem_wait(ptr->repletion);
		sem_wait(ptr->writing_sem);
		i++;
	}
	sem_post(ptr->end);
	return (NULL);
}

void	actions(t_main *ptr, int action)
{
	sem_wait(ptr->writing_sem);
	sem_wait(ptr->philosopher.rights);
	if (action == EAT)
	{
		print(ptr, &ptr->philosopher, "is eating");
		ptr->philosopher.last_meal = get_time();
	}
	else if (action == TAKE_FORK)
		print(ptr, &ptr->philosopher, "has taken a fork");
	else if (action == SLEEP)
	{
		print(ptr, &ptr->philosopher, "is sleeping");
		ptr->philosopher.meals++;
		if (ptr->philosopher.meals == ptr->meal_amount)
			sem_post(ptr->repletion);
	}
	else if (action == THINK)
		print(ptr, &ptr->philosopher, "is thinking");
	sem_post(ptr->philosopher.rights);
	sem_post(ptr->writing_sem);
}

void	routine(t_main *ptr)
{
	if (ptr->philosopher.philo_id % 2 == 0)
		ft_sleep(ptr, ptr->time_to_eat / 2);
	while (1)
	{
		actions(ptr, THINK);
		if (ptr->philosopher.meals != 0)
			ft_sleep(ptr, ((ptr->time_to_die) * 9) / 10 - (get_time()
					- ptr->philosopher.last_meal));
		sem_wait(ptr->forks);
		actions(ptr, TAKE_FORK);
		sem_wait(ptr->forks);
		actions(ptr, TAKE_FORK);
		actions(ptr, EAT);
		ft_sleep(ptr, ptr->time_to_eat);
		sem_post(ptr->forks);
		sem_post(ptr->forks);
		actions(ptr, SLEEP);
		ft_sleep(ptr, ptr->time_to_sleep);
	}
}

void	creat_philosopher(t_main *ptr)
{
	int	i;

	i = 0;
	ptr->start_time = get_time();
	while (i < ptr->phils_nb)
	{
		ptr->philosopher.philo_id = i + 1;
		ptr->philo_pid[i] = fork();
		if (ptr->philo_pid[i] == -1)
			ft_error(ptr, "fork", 1, errno);
		else if (ptr->philo_pid[i] == 0)
		{
			init_philosopher(ptr);
			routine(ptr);
		}
		i++;
	}
	sem_wait(ptr->end);
}
