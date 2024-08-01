/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:07:31 by shamdoun          #+#    #+#             */
/*   Updated: 2024/06/07 16:07:31 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		len;

	len = ft_strlen(s1);
	copy = ft_malloc(len + 1, 0);
	if (copy)
	{
		ft_memmove(copy, s1, len);
		copy[len] = '\0';
	}
	return (copy);
}

char	*ft_strdup_v3(const char *s1, int mode)
{
	char	*copy;
	int		len;

	len = ft_strlen(s1);
	copy = ft_malloc(len + 1, mode);
	if (copy)
	{
		ft_memmove(copy, s1, len);
		copy[len] = '\0';
	}
	return (copy);
}
