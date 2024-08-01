/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:01:57 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/22 20:25:50 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	count_int(int n)
{
	size_t	count;
	size_t	nbr;

	count = 0;
	nbr = n;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		count++;
		nbr = nbr / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	count;
	size_t	nbr;
	char	*s;

	count = count_int(n);
	s = malloc(count + 1);
	nbr = n;
	if (!s)
		return (NULL);
	s[count] = '\0';
	if (n < 0)
	{
		s[0] = '-';
		nbr = -nbr;
	}
	if (n == 0)
		s[0] = '0';
	while (nbr)
	{
		count--;
		s[count] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (s);
}

char	*ft_itoa_v2(int n)
{
	size_t	count;
	size_t	nbr;
	char	*s;

	count = count_int(n);
	s = ft_malloc(count + 1, 0);
	nbr = n;
	if (!s)
		return (NULL);
	s[count] = '\0';
	if (n < 0)
	{
		s[0] = '-';
		nbr = -nbr;
	}
	if (n == 0)
		s[0] = '0';
	while (nbr)
	{
		count--;
		s[count] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (s);
}
