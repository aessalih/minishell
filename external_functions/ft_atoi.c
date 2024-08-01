/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:41:49 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/31 21:23:11 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned char	*remove_spaces(unsigned char *s)
{
	while (*s == ' ' || *s == '\t'
		|| *s == '\n' || *s == '\r'
		|| *s == '\v' || *s == '\f')
		s++;
	return (s);
}

static int	return_status(char *s, int value, int flag)
{
	if (flag > 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (255);
	}
	if (*s)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (255);
	}
	return (value);
}

static int	max_value_reached(long result, char *s, int flag, int sign)
{
	if (flag)
	{
		if (result == 922337203685477580 && (*s == '8')
			&& (!(*(s + 1))) && sign < 0)
			return (1);
	}
	else if ((result > 922337203685477580
			|| ((result == 922337203685477580)
				&& (*s > '7'))))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				sign;
	long			result;
	unsigned char	*s;

	s = (unsigned char *)str;
	result = 0;
	sign = 1;
	s = remove_spaces(s);
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		if (max_value_reached(result, (char *)s, 1, sign))
			return (0);
		if (max_value_reached(result, (char *)s, 0, sign))
			return (return_status((char *)s, 0, 1));
		result = (result * 10) + (*s - '0');
		s++;
	}
	s = remove_spaces(s);
	return (return_status((char *)s, (int)result * sign, 0));
}
