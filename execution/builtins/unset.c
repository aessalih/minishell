/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:05:17 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/31 21:54:06 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	copy_list_excluding(char **new_environ, char **old_env, char *str)
{
	char	**p;
	int		i;

	i = 0;
	while (i < list_len(old_env))
	{
		p = ft_split_1(old_env[i], '=');
		if (!p)
			return ;
		if (ft_strncmp(str, p[0], ft_strlen(p[0]) + 1))
		{
			ft_memcpy(new_environ, &old_env[i], sizeof(char *));
			new_environ++;
		}
		i++;
	}
	*new_environ = NULL;
}

static int	r_path_empty(t_shell *shell, t_arg *data)
{
	if (!ft_strncmp(data->arg, "PATH", 5) && shell->r_path)
	{
		(shell->r_path = NULL);
		return (0);
	}
	return (1);
}

void	remove_env(t_arg *data, t_shell *shell, char ***env, int mode)
{
	char		**new_environ;
	int			error;

	error = 0;
	while (data && data->arg)
	{
		if (unset_syntax_error(data->arg))
			(error_status_update(UNSET_ERR, shell, 1), error = 1);
		else
		{
			if (r_path_empty(shell, data) && env_exists(data->arg, *env))
			{
				new_environ = ft_malloc(sizeof(char *) * (list_len(*env)), 2);
				if (!new_environ)
					return ;
				copy_list_excluding(new_environ, *env, data->arg);
				(*env = new_environ);
			}
			if (!error && mode)
				add_new_status(shell, 0);
		}
		data = data->next;
	}
}
