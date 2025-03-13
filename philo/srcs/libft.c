/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:09:47 by aouichou          #+#    #+#             */
/*   Updated: 2022/11/07 19:39:25 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str)
{
	long	neg;
	long	num;

	neg = 1;
	num = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num *= 10;
		num = num + (*str - '0');
		str++;
	}
	return (neg * num);
}

size_t	ft_strlen(const char *str)
{
	char	*temp;

	temp = (char *)str;
	while (*str)
		str++;
	return (str - temp);
}

void	ft_putstr_fd(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_isdigit(int c)
{
	if ((c < '0' || c > '9'))
		return (0);
	return (1);
}
