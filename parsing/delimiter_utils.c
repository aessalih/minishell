/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:49:14 by aessalih          #+#    #+#             */
/*   Updated: 2024/07/16 11:21:29 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_del(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1]
				&& (str[i + 1] == '"' || str[i + 1] == '\'')))
			return (1);
		i++;
	}
	return (0);
}

static int	numofexp(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && i > 0 && str[i - 1] == '$')
			break ;
		i++;
	}
	while (--i >= 0 && str[i] == '$')
		num++;
	return (num);
}

static int	ft_delimeterlen(char *str, int num)
{
	int	len;

	len = 0;
	if (num % 2 == 0)
	{
		while (str[len])
			len++;
	}
	else
	{
		while (str[len])
			len++;
		len -= 1;
	}
	return (len);
}

static char	*change_val(char *str, int num)
{
	char	*ptr;
	int		i;
	int		j;
	int		len;

	len = ft_delimeterlen(str, num);
	ptr = ft_malloc(len + 1, 2);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (str[i + 1] == '"'
				|| str[i + 1] == '\'') && num % 2 == 1)
			i++;
		ptr[j] = str[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*cut_exp(char *str)
{
	char	*ptr;
	int		i;
	int		num;

	i = check_del(str);
	if (i == 0)
		return (ptr = str, ptr);
	else
	{
		num = numofexp(str);
		ptr = change_val(str, num);
	}
	return (ptr);
}
