/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:03:17 by aouichou          #+#    #+#             */
/*   Updated: 2022/11/26 12:08:02 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	check_overflow(t_main *ptr, int ac, char **av)
{
	int		i;
	long	tmp;

	i = 0;
	while (++i < ac)
	{
		tmp = ft_atoi(av[i]);
		if (tmp > INT_MAX || tmp < INT_MIN || tmp < 1)
			return (ft_error(ptr, "Invalid arguments", 1, errno));
	}
	return (EXIT_SUCCESS);
}

int	check_args(t_main *ptr, int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	if (ac < 5 || ac > 6)
		return (ft_error(ptr, USAGE, 1, errno));
	while (++i < ac)
	{
		j = -1;
		if (!ft_strlen(av[i]))
			return (ft_error(ptr, "Empty argument", 1, errno));
		while (av[i][++j])
		{
			if (av[i][j] == '+')
			{
				if (!ft_isdigit(av[i][j + 1])
					|| (j != 0 && av[i][j - 1] != ' '))
					return (ft_error(ptr, "Invalid arguments", 1, errno));
				j++;
			}
			if (!ft_isdigit(av[i][j]) && av[i][j] != ' ')
				return (ft_error(ptr, "Invalid arguments", 1, errno));
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_main	*ptr;

	ptr = ft_get_ptr();
	if (!ptr || check_args(ptr, ac, av) || check_overflow(ptr, ac, av))
		return (EXIT_FAILURE);
	if (init_ptr(ptr, av) || creat_philosophers(ptr))
		return (EXIT_FAILURE);
	ft_free_ptr(ptr, 0);
	return (EXIT_SUCCESS);
}
