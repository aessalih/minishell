/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:08:51 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/10 12:43:17 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cpy_cat(char *dst, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
}

char	*ft_add_data1(char *data, char *buffer, int fd)
{
	int		read_bits;
	char	*tmp;

	read_bits = read(fd, buffer, BUFFER_SIZE);
	while (read_bits)
	{
		if (read_bits == -1)
			return (NULL);
		buffer[read_bits] = '\0';
		tmp = data;
		data = ft_strjoin_v2(tmp, buffer);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
		read_bits = read(fd, buffer, BUFFER_SIZE);
	}
	return (data);
}

char	*ft_update_buffer(char *b)
{
	int		i;
	char	*n;

	i = 0;
	while (b[i] && b[i] != '\n')
		i++;
	if (!b[i] || !b[1])
	{
		return (NULL);
	}
	n = ft_malloc(ft_strlen(b) - i, 0);
	if (!n)
		return (NULL);
	ft_memcpy(n, b + i + 1, ft_strlen(b) - i);
	if (*n == '\0')
		return (NULL);
	b[i + 1] = '\0';
	return (n);
}

char	*get_next_line(int fd)
{
	static char	*all_data;
	char		*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(all_data), all_data = NULL, NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!(buffer))
		return (NULL);
	result = ft_add_data1(all_data, buffer, fd);
	free(buffer);
	buffer = NULL;
	if (!result)
	{
		free(all_data);
		return (NULL);
	}
	all_data = ft_update_buffer(result);
	return (result);
}
