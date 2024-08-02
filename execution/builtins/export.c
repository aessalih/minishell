/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:22:06 by shamdoun          #+#    #+#             */
/*   Updated: 2024/08/01 17:19:03 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	append_mode(char *data)
{
	char	**split;

	split = ft_split_1(data, '=');
	return (split[0][ft_strlen(split[0]) - 1] == '+');
}

static void	update_env(char *env_name,
	t_shell *shell, char *data, char ***env)
{
	char		**new_environ;

	if (!ft_strchr(data, '='))
		return ;
	new_environ = ft_malloc(sizeof(char *) * (list_len(*env) + 1), 2);
	if (!new_environ)
		add_new_status(shell, errno);
	else
	{
		copy_list_updating(env_name, data, shell, new_environ);
		*env = new_environ;
	}
}

static char	*append_env(char *data)
{
	char	*name;
	char	*value;
	char	*result;

	name = ft_substr(data, 0, ft_strchr_index(data, '+'));
	if (!name)
		return (NULL);
	value = ft_strchr_occurence(data, '+') + 2;
	result = ft_strjoin(name, "=");
	if (!result)
		return (NULL);
	result = ft_strjoin(result, value);
	return (result);
}

static void	add_env(char *data, t_shell *shell, char ***env)
{
	char		**new_environ;
	char		*new_data;

	if (append_mode(data))
		new_data = append_env(data);
	else
		new_data = ft_strdup(data);
	if (!new_data)
		return ;
	new_environ = ft_malloc(sizeof(char *) * (list_len(*env) + 2), 2);
	if (!new_environ)
		add_new_status(shell, errno);
	else
	{
		ft_memcpy(new_environ, *env, list_len(*env) * sizeof(char *));
		new_environ[list_len(*env)] = new_data;
		new_environ[list_len(*env) + 1] = NULL;
		*env = new_environ;
	}
}

void	add_update_env(t_arg *data, t_shell *shell, char ***env, int mode)
{
	char	**split_env;
	int		error;

	if (mode && check_args(data, shell, env))
		return ;
	error = 0;
	while (data && data->arg)
	{
		if (export_syntax_error(data->arg))
			(error_status_update(EXPORT_ERR, shell, 1), error = 1);
		else
		{
			split_var(&split_env, data, shell);
			if (env_exists(split_env[0], *env))
				update_env(split_env[0], shell, data->arg, env);
			else
				add_env(data->arg, shell, env);
			if (!error && mode)
				add_new_status(shell, 0);
		}
		data = data->next;
	}
}
