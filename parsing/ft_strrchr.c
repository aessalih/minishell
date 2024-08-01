/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:13:35 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/04 11:00:40 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	char	value;
	char	*temp;

	value = (char) c;
	temp = NULL;
	while (*s)
	{
		if (*s == value)
		{
			temp = (char *)s;
		}
		s++;
	}
	if (*s == value)
		return ((char *)s);
	if (temp)
		return (temp);
	return (NULL);
}
