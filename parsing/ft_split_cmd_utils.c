/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:14:33 by aessalih          #+#    #+#             */
/*   Updated: 2024/07/31 21:16:20 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_lenwithoutquotes(char *str)
{
	char	q;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			q = str[i];
			i++;
			while (str[i] && str[i] != q)
				(1) && (i++, len++);
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*remove_quotes(char *str)
{
	char	*ptr;
	char	q;
	int		i;
	int		j;

	if (!str)
		return (0);
	i = ft_lenwithoutquotes(str);
	ptr = ft_malloc(i + 1, 0);
	(1) && (i = 0, j = 0);
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			(1) && (q = str[i], i++);
			while (str[i] && str[i] != q)
				(1) && (ptr[j] = str[i], j++, i++);
			i++;
		}
		else
			(1) && (ptr[j] = str[i], i++, j++);
	}
	return (ptr[j] = '\0', ptr);
}

void	put_delimiter(t_input *nw, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	nw->all_files->delimeter = malloc(i + 1);
	i = 0;
	while (str[i])
	{
		nw->all_files->delimeter[i] = str[i];
		i++;
	}
	nw->all_files->delimeter[i] = '\0';
}

void	put_filename(t_input *nw, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	nw->all_files->file_name = malloc(i + 1);
	i = 0;
	while (str[i])
	{
		nw->all_files->file_name[i] = str[i];
		i++;
	}
	nw->all_files->file_name[i] = '\0';
}

void	put_cmdname(t_input *nw, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	nw->command_name = malloc(i + 1);
	i = 0;
	while (str[i])
	{
		nw->command_name[i] = str[i];
		i++;
	}
	nw->command_name[i] = '\0';
}
