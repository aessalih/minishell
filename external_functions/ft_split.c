/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:08:46 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/22 10:24:12 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_skipchar(char *str)
{
	char	q;

	while (*str && *str != ' ' && *str != '\t')
	{
		if (*str == '"' || *str == '\'')
		{
			q = *str;
			str++;
			while (*str != q)
				str++;
			str++;
		}
		else
			str++;
	}
	return (str);
}

static int	words(char *str)
{
	int		count;
	char	q;

	count = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			count++;
			q = *(str++);
			while (*str != q)
				str++;
			str++;
		}
		else if (*str == ' ' || *str == '\t')
			str++;
		else
		{
			count++;
			str = ft_skipchar(str);
		}
	}
	return (count);
}

static int	ft_strlenght(char *str)
{
	int		len;
	char	q;

	len = 0;
	while (*str && *str != ' ' && *str != '\t')
	{
		if (*str == '"' || *str == '\'')
		{
			q = *(str++);
			len++;
			while (*str && *str != q)
				(1) && (str++, len++);
		}
		(1) && (str++, len++);
	}
	return (len);
}

static char	*ft_fillstr(char *str)
{
	char	q;
	char	*val;
	int		i;
	int		len;

	(1) && (i = 0, len = ft_strlenght(str));
	val = malloc(len + 1);
	if (!val)
		return (NULL);
	while (*str && *str != ' ' && *str != '\t')
	{
		if (*str == '"' || *str == '\'')
		{
			q = *str;
			val[i++] = *str;
			while (*(++str) != q)
				val[i++] = *str;
			val[i] = *str;
		}
		else
			val[i] = *str;
		(1) && (i++, str++);
	}
	val[i] = '\0';
	return (val);
}

char	**ft_split(char *s)
{
	t_v	v;

	(1) && (v.j = words(s), v.p = malloc(sizeof(char *) * (v.j + 1)), v.j = 0);
	if (!v.p)
		return (NULL);
	while (*s)
	{
		if (*s != ' ' && *s != '\t')
			(1) && (v.p[v.j] = ft_fillstr(s), v.j++);
		if (v.j != 0 && v.p[v.j - 1] == NULL)
			return (ft_free(v.p, v.j), NULL);
		while (*s && *s != ' ' && *s != '\t')
		{
			if (*s == '\'' || *s == '"')
			{
				v.q = *(s++);
				while (*s && *s != v.q)
					s++;
			}
			s++;
		}
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
	}
	return (v.p[v.j] = NULL, v.p);
}
