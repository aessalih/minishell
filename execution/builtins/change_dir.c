/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:03:49 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/22 10:04:03 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getenv(char *name, char **env)
{
	char	**split;
	char	*found;

	while (*env)
	{
		split = ft_split_1(*env, '=');
		if (!split)
			return (NULL);
		if (!ft_strncmp(split[0], name, ft_strlen(name) + 1))
		{
			found = ft_strdup(split[1]);
			if (!found)
				return (NULL);
			return (found);
		}
		env++;
	}
	return (NULL);
}

void	update_cwd(char *cwd, t_arg *path, char *old_cwd)
{
	char	**split_cwd;
	char	**split_path;
	char	*joined;	
	int		i;

	if (check_path(path, cwd))
		return ;
	if (split_values(&split_cwd, &split_path, cwd, path))
		return ;
	joined = ft_strdup("/");
	if (!joined)
		return ;
	copy_old_cwd(old_cwd, split_cwd);
	i = copy_common_path(&joined, split_cwd,
			split_path[0]);
	copy_unique_path(&joined, split_cwd, split_path, i);
	ft_strcpy(cwd, joined);
}

static int	change_to_default_home(t_shell *shell, char **env, int *rv)
{
	char	*home;

	home = ft_getenv("HOME", env);
	if (!home)
	{
		(write(2, "bash: cd: HOME not set\n", 23), add_new_status(shell, 1));
		return (1);
	}
	*rv = chdir(home);
	return (0);
}

static void	update_wd(t_shell *shell,
		int return_value, t_arg *path,
			char *old_cwd)
{
	char	*gcw_result;

	gcw_result = getcwd(shell->cwd, sizeof(shell->cwd));
	if (gcw_result)
	{
		update_oldpwd(old_cwd, shell);
		if (!return_value && path)
			update_cwd(shell->cwd, path, old_cwd);
	}
	else
	{
		ft_putstr_fd(GCW_FAILED, 2);
		old_cwd = ft_strjoin(old_cwd, "/");
		if (!old_cwd)
			return ;
		old_cwd = ft_strjoin(old_cwd, path->arg);
		if (!old_cwd)
			return ;
		ft_strcpy(shell->cwd, old_cwd);
	}
}

void	change_directory(t_arg *path, t_shell *shell, char ***env)
{
	int			return_value;
	char		*old_cwd;

	return_value = 0;
	old_cwd = ft_strdup(shell->cwd);
	if (!old_cwd)
	{
		add_new_status(shell, 1);
		return ;
	}
	while (path && !path->arg)
		path = path->next;
	if (path && path->arg && !ft_strlen(path->arg))
		return ;
	if (path && path->arg && ft_strncmp(path->arg, "~", 2))
		return_value = chdir(path->arg);
	else if (change_to_default_home(shell, *env, &return_value))
		return ;
	if (return_value)
	{
		(add_new_status(shell, 1), perror("minishell: cd"));
		return ;
	}
	update_wd(shell, return_value, path, old_cwd);
}
