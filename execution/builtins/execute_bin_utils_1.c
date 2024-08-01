/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:55:46 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/24 20:49:37 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bin_exists(char *s)
{
	int	a;
	int	b;
	int	c;
	int	d;

	a = !ft_strncmp(s, "/bin/", 5) && s[6];
	b = !ft_strncmp(s, "/usr/bin/", 9) && s[10];
	c = !ft_strncmp(s, "/sbin/", 6) && s[7];
	d = !ft_strncmp(s, "/usr/sbin/", 10) && s[11];
	return (a || b || c || d);
}

int	incorrect_syntax(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/' && s[i + 1] && s[i + 1] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	empty_string(char *s)
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

void	update_command_name(t_shell *shell)
{
	while (shell->all_input->command_name[0]
		&& shell->all_input->command_name[0] == '/'
		&& shell->all_input->command_name[1]
		&& shell->all_input->command_name[1] == '/')
		shell->all_input->command_name++;
}

int	is_directory(char *path, t_shell *shell)
{
	DIR		*dir;
	char	*tmp;

	tmp = path;
	if (*path == '.')
		path = ft_strjoin_v2(shell->cwd, &path[1]);
	if (!path)
		return (0);
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	else
		return (0);
}
