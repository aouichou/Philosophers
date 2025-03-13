/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:29:40 by aouichou          #+#    #+#             */
/*   Updated: 2022/12/12 18:30:35 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_main *ptr)
{
	long	i;

	i = 0;
	memset(ptr->philosophers, 0, sizeof(t_philo) * ptr->phils_nb);
	while (i < ptr->phils_nb)
	{
		ptr->philosophers[i].ptr = ptr;
		ptr->philosophers[i].philo_id = i + 1;
		ptr->philosophers[i].meals = 0;
		ptr->philosophers[i].last_meal = 0;
		ptr->philosophers[i].stop = 0;
		ptr->philosophers[i].left_fork = &(ptr->forks[i]);
		ptr->philosophers[i].right_fork = &(ptr->forks[(i + 1)
				% ptr->phils_nb]);
		i++;
	}
}

int	init_ptr(t_main *ptr, char **av)
{
	long	i;

	ptr->end = 0;
	ptr->start_time = 0;
	ptr->phils_nb = ft_atoi(av[1]);
	ptr->time_to_die = ft_atoi(av[2]);
	ptr->time_to_eat = ft_atoi(av[3]);
	ptr->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		ptr->meal_amount = ft_atoi(av[5]);
	ptr->philosophers = malloc(ptr->phils_nb * sizeof(t_philo));
	ptr->forks = malloc(ptr->phils_nb * sizeof(pthread_mutex_t));
	if (!(ptr->philosophers) || !(ptr->forks))
		return (ft_error(ptr, "Malloc", 1, errno));
	memset(ptr->forks, 0, sizeof(pthread_mutex_t) * ptr->phils_nb);
	i = -1;
	while (++i < ptr->phils_nb)
		if (pthread_mutex_init(&(ptr->forks[i]), NULL))
			return (ft_error(ptr, "pthread init", 1, errno));
	if (pthread_mutex_init(&(ptr->writing_mutex), NULL))
		return (ft_error(ptr, "pthread init", 1, errno));
	init_philo(ptr);
	return (EXIT_SUCCESS);
}
