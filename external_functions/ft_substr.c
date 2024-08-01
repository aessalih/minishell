/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:00:12 by shamdoun          #+#    #+#             */
/*   Updated: 2024/06/07 15:41:20 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_len(char const *s, size_t *len, unsigned int start)
{
	if (*len > ft_strlen(s)
		|| start + *len > (unsigned long)ft_strlen(s))
		*len = ft_strlen(s) - start;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sbs;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	if (len < 1 || start >= ft_strlen(s))
		return (ft_strdup(""));
	check_len(s, &len, start);
	sbs = ft_malloc(sizeof(char) * len + 1, 2);
	if (!sbs)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			sbs[j++] = s[i];
		i++;
	}
	sbs[j] = '\0';
	return (sbs);
}
