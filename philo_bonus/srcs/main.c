/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:35:12 by aouichou          #+#    #+#             */
/*   Updated: 2022/12/09 18:08:12 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_main	*ft_get_ptr(void)
{
	static t_main	*ptr = NULL;

	if (!ptr)
	{
		ptr = (t_main *)malloc(sizeof(t_main));
		if (!(ptr))
			return (NULL);
		memset(ptr, 0, sizeof(t_main));
	}
	return (ptr);
}

void	check_overflow(t_main *ptr, int ac, char **av)
{
	int		i;
	long	tmp;

	i = 0;
	while (++i < ac)
	{
		tmp = ft_atoi(av[i]);
		if (tmp > INT_MAX || tmp < INT_MIN || tmp < 1)
			ft_error(ptr, "Invalid arguments", 1, errno);
	}
}

void	check_args(t_main *ptr, int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	if (ac < 5 || ac > 6)
		ft_error(ptr, USAGE, 1, errno);
	while (++i < ac)
	{
		j = 0;
		if (!ft_strlen(av[i]))
			ft_error(ptr, "Empty argument", 1, errno);
		while (av[i][j])
		{
			if (av[i][j] == '+')
			{
				if (!ft_isdigit(av[i][j + 1])
					|| (j != 0 && av[i][j - 1] != ' '))
					ft_error(ptr, "Invalid arguments", 1, errno);
				j++;
			}
			if (!ft_isdigit(av[i][j]) && av[i][j] != ' ')
				ft_error(ptr, "Invalid arguments", 1, errno);
			j++;
		}
	}
}

int	main(int ac, char **av)
{
	t_main	*ptr;

	ptr = ft_get_ptr();
	if (!ptr)
	{
		ft_error(ptr, "malloc", 0, errno);
		return (EXIT_FAILURE);
	}
	check_args(ptr, ac, av);
	check_overflow(ptr, ac, av);
	init_ptr(ptr, av);
	creat_philosopher(ptr);
	ft_free_ptr(ptr);
	return (0);
}
