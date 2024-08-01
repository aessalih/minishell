/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:19:52 by aessalih          #+#    #+#             */
/*   Updated: 2024/07/31 21:19:36 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strlenexin(char *cmd, int *v)
{
	int	len;
	int	i;

	(1) && (len = 0, i = 0);
	while (cmd && cmd[i] && cmd[i] != '$')
	{
		if (*v == 0)
		{
			if (cmd[i] == '\'')
			{
				(1) && (len++, i++);
				while (cmd[i] && cmd[i] != '\'')
					(1) && (i++, len++);
			}
			(1) && (len++, i++);
		}
		else
			(1) && (len++, i++);
		if (cmd[i] == '"')
			*v = 0;
		if (cmd[i] == '$' && cmd[i + 1]
			&& ft_strchr(" \t'.#!%%&()*+,-/:;<=>@[]\\^{}|~", cmd[i + 1]))
			(1) && (i++, len++);
	}
	return (len);
}

static char	*ft_put_str(char *cmd, int len, int *v)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(len + 1);
	while (cmd[i] && cmd[i] != '$')
	{
		if (*v == 0)
		{
			if (cmd[i] == '\'')
			{
				str[i] = cmd[i];
				i++;
				while (cmd[i] && cmd[i] != '\'')
					(1) && (str[i] = cmd[i], i++);
			}
			(1) && (str[i] = cmd[i], i++);
		}
		if (*v == 1)
			(1) && (str[i] = cmd[i], i++);
		if (cmd[i] == '"')
			*v = 0;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strlenquotes(char *str)
{
	char	*del;
	int		len;
	int		i;

	del = " \t'\".#!%%&()*+,-/:;<=>@[]\\^{}|~$";
	i = 1;
	len = 0;
	if (str[i] >= '0' && str[i] <= '9')
	{
		len = 1;
		return (len);
	}
	while (str[i] && !ft_strchr(del, str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

static void	ft_joinoutex(t_normalExpVar *v, char *cmd)
{
	(*v).l = ft_strlenexin(cmd + (*v).i, &(*v).v);
	(*v).p = ft_put_str(cmd + (*v).i, (*v).l, &(*v).v);
	(*v).s = ft_join(&(*v).s, (*v).p);
	free((*v).p);
	(*v).i += (*v).l - 1;
	(*v).l = 0;
	(*v).i++;
}

char	*ft_expand(char *cmd, t_shell *shell)
{
	t_normalExpVar	v;

	(1) && (v.i = 0, v.v = 0, v.s = NULL, v.l = 0);
	while (cmd[v.i])
	{
		if (cmd[v.i] == '$')
		{
			v.l = ft_strlenquotes(cmd + v.i);
			v.p = ft_getname(cmd + v.i, shell, v.l);
			(1) && (v.i += v.l + 1, v.s = ft_join(&v.s, v.p));
			free(v.p);
		}
		if (v.v == 0 && cmd[v.i] == '"')
			v.v = 1;
		else if (cmd[v.i] == '"')
			v.v = 0;
		if (cmd[v.i])
			ft_joinoutex(&v, cmd);
	}
	return (v.s);
}
