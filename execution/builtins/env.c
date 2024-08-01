/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:45:04 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/31 21:51:01 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_underscore_var(t_arg *new_envpath, char *value)
{
	int		i;
	char	**array;

	i = 0;
	array = ft_split_1(value, ' ');
	if (!array)
		return ;
	value = NULL;
	while (array[i])
	{
		value = ft_strjoin_v2(value, array[i]);
		if (!value)
			return ;
		if (array[i + 1])
		{
			value = ft_strjoin(value, " ");
			if (!value)
				return ;
		}
		i++;
	}
	(new_envpath)->arg = ft_strjoin("_=", value);
}

static int	is_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	update_env_path_var(t_shell *shell, char *value, int mode)
{
	t_arg	*new_envpath;

	new_envpath = ft_malloc(sizeof(t_arg), 0);
	if (!new_envpath)
	{
		perror("failed!");
		return ;
	}
	if (value && is_empty(value))
		value = NULL;
	if ((!mode && !value) || (!mode && !ft_strncmp(value, "", 1)))
		new_envpath->arg = ft_strdup("_");
	else if (!value)
		new_envpath->arg = ft_strdup("_=/usr/bin/env");
	else if (mode)
		new_envpath->arg = ft_strjoin("_=/usr/bin/", value);
	else
		update_underscore_var(new_envpath, value);
	new_envpath->next = NULL;
	if (!mode && !value)
		remove_env(new_envpath, shell, &shell->env, 0);
	else
		add_update_env(new_envpath, shell, &shell->env, 0);
}

void	add_default_env(t_shell *shell)
{
	t_arg	*tmp;
	char	*pwd;

	tmp = malloc(sizeof(t_arg));
	pwd = ft_strjoin("PWD=", shell->cwd);
	tmp->arg = pwd;
	tmp->next = NULL;
	add_update_env(tmp, shell, &shell->env, 0);
	tmp->arg = ft_strdup("SHLVL=1");
	tmp->next = NULL;
	add_update_env(tmp, shell, &shell->env, 0);
	free(tmp);
}

void	update_inhereted_env(t_shell *shell)
{
	t_arg	*oldpwd;

	oldpwd = ft_malloc(sizeof(t_arg), 0);
	oldpwd->arg = ft_strdup("OLDPWD");
	oldpwd->next = NULL;
	remove_env(oldpwd, shell, &shell->env, 0);
	update_shlvl(shell);
}
