/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:19:01 by aessalih          #+#    #+#             */
/*   Updated: 2024/07/31 21:18:46 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_cmdlenght(char *s)
{
	int		len;
	int		i;
	char	o;

	(1) && (len = 0, i = 0);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			o = s[i++];
			len++;
			while (s && s[i] != o)
				(1) && (len++, i++);
		}
		if (s[i] == '<' || s[i] == '>')
		{
			o = s[i];
			if (i > 0 && s[i - 1] != o && s[i - 1] != ' ' && s[i - 1] != '\t')
				len++;
			if (s[i + 1] != o && s[i + i] != ' ' && s[i + 1] != '\t')
				len++;
		}
		(1) && (i++, len++);
	}
	return (len);
}

static char	*putstring(char *s, t_space *v)
{
	while (s[v->i])
	{
		if (s[v->i] == '\'' || s[v->i] == '"')
		{
			(1) && (v->o = s[v->i], v->p[v->j++] = s[v->i++]);
			while (s[v->i] != v->o)
				v->p[v->j++] = s[v->i++];
		}
		if (v->i > 0 && ((s[v->i] == '>' && s[v->i - 1] != '>')
				|| (s[v->i] == '<' && s[v->i - 1] != '<')))
		{
			if (v->i > 0 && (s[v->i - 1] != ' ' && s[v->i - 1] != '\t'))
				(1) && (v->p[v->j] = ' ', v->p[++v->j] = s[v->i], v->l = 1);
		}
		if (s[v->i + 1] && ((s[v->i] == '>' && s[v->i + 1] != '>')
				|| (s[v->i] == '<' && s[v->i + 1] != '<')))
		{
			if (s[v->i + 1] != ' ' && s[v->i + 1] != '\t')
				(1) && (v->p[v->j] = s[v->i], v->p[++v->j] = ' ', v->l = 1);
		}
		if (v->l == 0)
			v->p[v->j] = s[v->i];
		(1) && (v->l = 0, v->j++, v->i++);
	}
	return (v->p[v->j] = '\0', v->p);
}

static char	*ft_strwithspace(char *s)
{
	t_space	v;

	(1) && (v.i = 0, v.j = 0, v.l = ft_cmdlenght(s));
	v.p = malloc(v.l + 1);
	v.l = 0;
	putstring(s, &v);
	return (free(s), v.p);
}

void	add_space(t_commands *cmd)
{
	while (cmd)
	{
		cmd->command = ft_strwithspace(cmd->command);
		cmd = cmd->next;
	}
}
