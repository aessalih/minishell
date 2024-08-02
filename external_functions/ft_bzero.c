/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:11:21 by shamdoun          #+#    #+#             */
/*   Updated: 2024/08/02 15:16:14 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*dst;

	dst = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
}

void	update_sign(unsigned char **s, int *sign)
{
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			(*sign) *= -1;
		(*s)++;
	}
}
