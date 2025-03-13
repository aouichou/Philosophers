/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:28:56 by aouichou          #+#    #+#             */
/*   Updated: 2022/12/12 18:30:35 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print(t_philo *philosopher, char *action)
{
	time_t	time;

	time = get_time() - philosopher->ptr->start_time;
	printf("%ld %d %s\n", time, philosopher->philo_id, action);
}

void	ft_free_ptr(t_main *ptr, int i)
{
	while (i < ptr->phils_nb)
	{
		if (pthread_join(ptr->philosophers[i].philosopher, NULL))
			ft_error(ptr, "pthread join", 0, errno);
		i++;
	}
	if (ptr->philosophers)
		free(ptr->philosophers);
	i = 0;
	if (ptr->forks)
	{
		while (i < ptr->phils_nb)
		{
			if (pthread_mutex_destroy(&(ptr->forks[i])))
				ft_error(ptr, "mutex destroy", 0, errno);
			i++;
		}
		free(ptr->forks);
	}
	if (pthread_mutex_destroy(&(ptr->writing_mutex)))
		ft_error(ptr, "mutex destroy", 0, errno);
	free(ptr);
}

int	ft_error(t_main *ptr, char *error, int mod_exit, int rno)
{
	pthread_mutex_lock(&(ptr->writing_mutex));
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	if (rno == EINVAL)
		ft_putstr_fd(" Invalid argument", STDERR_FILENO);
	else if (rno == EBUSY)
		ft_putstr_fd(" Device or resource busy", STDERR_FILENO);
	else if (rno == EAGAIN)
		ft_putstr_fd(" Try again", STDERR_FILENO);
	else if (rno == ENOMEM)
		ft_putstr_fd(" Out of memory", STDERR_FILENO);
	else if (rno == EPERM)
		ft_putstr_fd(" Operation not permitted", STDERR_FILENO);
	else
		ft_putstr_fd(" Undefined error", STDERR_FILENO);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(BLANK, STDERR_FILENO);
	pthread_mutex_unlock(&(ptr->writing_mutex));
	if (mod_exit)
	{
		ft_free_ptr(ptr, 0);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

void	ft_sleep(t_main *ptr, time_t sleep_time)
{
	time_t	start;

	start = get_time();
	while (get_time() - start < sleep_time)
	{
		pthread_mutex_lock(&(ptr->writing_mutex));
		if (ptr->end == 1)
		{
			pthread_mutex_unlock(&(ptr->writing_mutex));
			break ;
		}
		pthread_mutex_unlock(&(ptr->writing_mutex));
		if (ptr->phils_nb < 100)
			usleep(10);
		else
			usleep(100);
	}
}
