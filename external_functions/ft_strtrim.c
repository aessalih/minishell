/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:04:39 by shamdoun          #+#    #+#             */
/*   Updated: 2024/06/07 15:41:17 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;

	start = 0;
	if (!s1 || !set)
	{
		return (NULL);
	}
	end = ft_strlen(s1);
	if (!end)
		return (ft_strdup(s1));
	while (ft_in_set(s1[start], set))
		start++;
	while (ft_in_set(s1[end - 1], set))
		end--;
	if (start >= end)
		return (ft_strdup(""));
	result = ft_substr(s1, start, end - start);
	if (!result)
		return (NULL);
	return (result);
}
