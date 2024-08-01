/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:06:15 by shamdoun          #+#    #+#             */
/*   Updated: 2024/06/07 16:06:26 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strchr_occurence(const char *s, int c)
{
	char	value;
	int		i;

	value = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == value)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == value)
		return ((char *)(s + i));
	return (NULL);
}

int	ft_strchr_index(const char *s, int c)
{
	char	value;
	int		i;

	value = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == value)
			return (i);
		i++;
	}
	if (s[i] == value)
		return (i);
	return (0);
}
