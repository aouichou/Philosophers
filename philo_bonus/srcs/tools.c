/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:27:00 by aouichou          #+#    #+#             */
/*   Updated: 2022/12/12 18:30:35 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print(t_main *ptr, t_philo *philosopher, char *action)
{
	time_t	time;

	time = get_time() - ptr->start_time;
	printf("%ld %ld %s\n", time, philosopher->philo_id, action);
}

void	ft_error(t_main *ptr, char *error, int mod_exit, int rno)
{
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
	if (mod_exit)
	{
		ft_free_ptr(ptr);
		exit(-1);
	}
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
		if (ptr->phils_nb < 100)
			usleep(5);
		else
			usleep(50);
	}
}

char	*naming_semaphores(int philo_id)
{
	int		i;
	int		tmp;
	char	*name;

	i = 2;
	tmp = philo_id;
	while (tmp > 9)
	{
		tmp /= 10;
		i++;
	}
	name = (char *)malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	memset(name, 0, i + 1);
	name[0] = 'S';
	name[i--] = '\0';
	while (philo_id > 9)
	{
		name[i] = philo_id % 10 + '0';
		philo_id /= 10;
		i--;
	}
	name[i] = philo_id % 10 + '0';
	return (name);
}
