/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:50:11 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/22 12:58:27 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	command_is_executable(char *env, char *s)
{
	char	**split1;
	char	**split2;
	int		i;

	split1 = ft_split_1(env, '/');
	if (!split1)
		return (0);
	split2 = ft_split_1(s, '/');
	if (!split2)
		return (0);
	i = 0;
	while (split1[i] && split2[i])
	{
		if (ft_strncmp(split1[i], split2[i], ft_strlen(split2[i])))
			return (0);
		i++;
	}
	if (split1[i] && split2[i] && (access(s, F_OK | X_OK) == 0))
		return (1);
	return (0);
}

static char	*extract_command(char *s, char **env_list, char *command)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env_list[i])
	{
		if (command_is_executable(env_list[i], s))
			return (ft_strdup(s));
		tmp = ft_strjoin(env_list[i], "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, s);
		if (!command)
			return (NULL);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *s, t_shell *shell)
{
	char	**env_list;
	char	*command;
	char	*path;

	command = NULL;
	env_list = NULL;
	if (s[0] == '\0')
		return (NULL);
	if (shell->r_path)
		env_list = ft_split_1(shell->r_path, ':');
	else
	{
		path = ft_getenv("PATH", shell->env);
		if (!path)
			return (NULL);
		env_list = ft_split_1(path, ':');
	}
	if (!env_list)
		return (NULL);
	return (extract_command(s, env_list, command));
}

void	copy_list_updating(char *env_name, char *data,
	t_shell *shell, char **new_environ)
{
	char	**old_list;
	char	**p;
	int		i;

	i = 0;
	old_list = shell->env;
	while (i < list_len(old_list))
	{
		p = ft_split_1(old_list[i], '=');
		if (!p)
			return ;
		if (ft_strncmp(env_name, p[0], ft_strlen(p[0]) + 1))
			ft_memcpy(new_environ, &old_list[i], sizeof(char *));
		else
			update_list_value(data, old_list[i], new_environ);
		new_environ++;
		i++;
	}
	*new_environ = NULL;
}

void	add_a_data_to_linked_list(t_a_data **list, void *address)
{
	t_a_data	*new;

	new = ft_lstnew_ad(address);
	if (!new)
		return ;
	ft_lst_add_ad_back(list, new);
}
