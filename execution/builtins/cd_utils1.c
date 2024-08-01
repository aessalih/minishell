/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:19:10 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/10 09:18:28 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_old_cwd(char *old_cwd, char **split_cwd)
{
	char	**split_oldcwd;
	int		i;

	i = 0;
	split_oldcwd = ft_split_1(old_cwd, '/');
	if (!split_oldcwd)
		return ;
	while (split_cwd[i] && split_oldcwd[i])
	{
		if (ft_same_value(split_cwd[i], split_oldcwd[i]))
			ft_strcpy(split_cwd[i], split_oldcwd[i]);
		i++;
	}
}

static void	ft_update_if_already_exists(char **split_cwd, char *value, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		if (ft_same_value(split_cwd[i], value))
		{
			ft_strcpy(split_cwd[i], value);
			return ;
		}
		i++;
	}
}

void	update_cwd_list(char **split_cwd, char **split_path, int k)
{
	int	j;

	j = 0;
	while (split_path[j])
	{
		if (split_cwd[k])
		{
			if (ft_same_value(split_cwd[k], split_path[j]))
			{
				ft_strcpy(split_cwd[k], split_path[j]);
				k++;
			}
			else
				ft_update_if_already_exists(split_cwd, split_path[j], k);
		}
		else
			ft_update_if_already_exists(split_cwd, split_path[j], k);
		j++;
	}
}

int	path_is_only_levels(char **split)
{
	while (*split)
	{
		if (ft_strncmp(*split, "..", ft_strlen(*split)))
			return (0);
		split++;
	}
	return (1);
}

void	update_oldpwd(char *old_pwd, t_shell *shell)
{
	t_arg	*oldpwd_env;
	char	*tmp;

	oldpwd_env = ft_malloc(sizeof(t_arg), 0);
	if (!oldpwd_env)
	{
		add_new_status(shell, 1);
		return ;
	}
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (!tmp)
	{
		add_new_status(shell, 1);
		return ;
	}
	oldpwd_env->arg = tmp;
	oldpwd_env->next = NULL;
	add_update_env(oldpwd_env, shell, &shell->env, 0);
}
