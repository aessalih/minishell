/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:08:06 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/11 11:33:08 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	result = ft_malloc(len + 1, 0);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, ft_strlen(s1) + 1);
	ft_strlcat(result, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	return (result);
}

char	*ft_join(char **s1, char *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	if (!(*s1) && !s2)
		return (NULL);
	ptr = (char *) ft_malloc((ft_strlen((*s1))
				+ ft_strlen(s2) + 1) * sizeof(char), 0);
	if (ptr == NULL)
		return (NULL);
	while ((*s1) && (*s1)[i])
	{
		*(char *)(ptr + i) = *(char *)((*s1) + i);
		i++;
	}
	while (s2 && s2[j])
	{
		*(char *)(ptr + i + j) = *(char *)(s2 + j);
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}
