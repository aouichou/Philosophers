/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:11:01 by aouichou          #+#    #+#             */
/*   Updated: 2022/12/12 18:30:35 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	kill_philosophers(t_main *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->phils_nb)
		kill(ptr->philo_pid[i++], SIGKILL);
}

void	ft_free_ptr(t_main *ptr)
{
	kill_philosophers(ptr);
	if (ptr->end && sem_close(ptr->end))
		ft_error(ptr, "sem close", 0, errno);
	if (ptr->forks && sem_close(ptr->forks))
		ft_error(ptr, "sem close", 0, errno);
	if (ptr->meal_amount && sem_close(ptr->repletion))
		ft_error(ptr, "sem close", 0, errno);
	if (ptr->writing_sem && sem_close(ptr->writing_sem))
		ft_error(ptr, "sem close", 0, errno);
	free(ptr->philo_pid);
	free(ptr);
}
