/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:31:10 by aouichou          #+#    #+#             */
/*   Updated: 2022/12/12 18:30:55 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	init_philosopher(t_main *ptr)
{
	char	*name;

	name = naming_semaphores(ptr->philosopher.philo_id);
	ptr->philosopher.last_meal = ptr->start_time;
	sem_unlink(name);
	ptr->philosopher.rights
		= sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	if (!(ptr->philosopher.rights))
		ft_error(ptr, "sem open a", 1, errno);
	sem_unlink("/forks");
	sem_unlink("speak");
	sem_unlink("stop");
	sem_unlink("repletion");
	free(name);
	if (pthread_create(&ptr->philosopher.death_monitor, NULL,
			&check_death, ptr))
		ft_error(ptr, "pthread", 1, errno);
	pthread_detach(ptr->philosopher.death_monitor);
}

void	init_thread(t_main *ptr)
{
	if (ptr->meal_amount)
	{
		if (pthread_create(&ptr->repletion_monitor,
				NULL, &check_repletion, ptr))
			ft_error(ptr, "pthread", 1, errno);
		pthread_detach(ptr->repletion_monitor);
	}
}

void	init_semaphores(t_main *ptr)
{
	sem_unlink("/forks");
	sem_unlink("writing_sem");
	sem_unlink("repletion");
	sem_unlink("end");
	if (ptr->phils_nb > 2)
		ptr->forks = sem_open("/forks", O_CREAT | O_EXCL, 0666,
				ptr->phils_nb - 2);
	else
		ptr->forks = sem_open("/forks", O_CREAT | O_EXCL, 0666, ptr->phils_nb);
	ptr->writing_sem = sem_open("writing_sem", O_CREAT | O_EXCL, 0644, 1);
	ptr->end = sem_open("end", O_CREAT | O_EXCL, 0644, 0);
	if (ptr->meal_amount)
		ptr->repletion = sem_open("repletion", O_CREAT | O_EXCL, 0644, 0);
	if (!ptr->forks || !ptr->writing_sem || !ptr->end
		|| (ptr->meal_amount && !ptr->repletion))
		ft_error(ptr, "sem_open", 1, errno);
	if (ptr->phils_nb > 2)
	{
		sem_post(ptr->forks);
		sem_post(ptr->forks);
	}
	sem_unlink("/forks");
	sem_unlink("writing_sem");
	sem_unlink("repletion");
	sem_unlink("end");
}

void	init_ptr(t_main	*ptr, char **av)
{
	ptr->start_time = 0;
	ptr->phils_nb = ft_atoi(av[1]);
	ptr->time_to_die = ft_atoi(av[2]);
	ptr->time_to_eat = ft_atoi(av[3]);
	ptr->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		ptr->meal_amount = ft_atoi(av[5]);
	ptr->philo_pid = (pid_t *)malloc(sizeof(pid_t) * ptr->phils_nb);
	if (!(ptr->philo_pid))
		ft_error(ptr, "malloc", 1, errno);
	memset(ptr->philo_pid, 0, sizeof(pid_t) * ptr->phils_nb);
	init_semaphores(ptr);
	init_thread(ptr);
}
