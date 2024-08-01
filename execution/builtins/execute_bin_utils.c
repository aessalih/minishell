/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:26:31 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/28 22:12:17 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_args_list(t_shell *shell, char ***args_list)
{
	char	*joined_args;

	if (shell->all_input->args)
	{
		joined_args = ft_join_args(shell->all_input->args);
		if (!joined_args)
			return ;
		*args_list = ft_split_1(joined_args, ' ');
		if (!(*args_list))
			return ;
		update_split_list(args_list, shell->all_input->command_name);
	}
	else
	{
		*args_list = ft_split_1(shell->all_input->command_name, ' ');
		if (!(*args_list))
			return ;
	}
}

int	correct_dir(char *cmd_path, char *cwd)
{
	char	**split1;
	char	**split2;

	split1 = ft_split_1(cmd_path, '/');
	if (!split1)
		return (0);
	split2 = ft_split_1(cwd, '/');
	if (!split2)
		return (0);
	if (!ft_strncmp(split1[list_len(split1) - 3],
			split2[list_len(split2) - 1],
			ft_strlen(split2[list_len(split2) - 1])))
		return (1);
	return (0);
}

void	make_file_executable(char ***args, char *file, char **cmd_path)
{
	*cmd_path = ft_strdup("/bin/bash");
	*args = ft_malloc(sizeof(char *) * 4, 1);
	if (!(*args))
		return ;
	(*args)[0] = *cmd_path;
	(*args)[1] = "-c";
	(*args)[2] = file;
	(*args)[3] = NULL;
}

int	is_file(char *path, t_shell *shell)
{
	char	*tmp;
	int		fd;

	if (!path[0])
		return (0);
	tmp = ft_strjoin_v2(shell->cwd, &path[1]);
	fd = open(tmp, O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		return (1);
	}
	else
		return (0);
}

int	execution_case(char *cmd_path, t_shell *shell)
{
	if (is_directory(shell->all_input->command_name, shell)
		&& (*shell->all_input->command_name == '.'
			|| *shell->all_input->command_name == '/'))
		return (7);
	if (cmd_path && (*shell->all_input->command_name == '.')
		&& ((access(shell->all_input->command_name, F_OK | X_OK) == 0))
		&& !correct_dir(cmd_path, shell->cwd))
		return (1);
	else if (cmd_path && (*shell->all_input->command_name == '.')
		&& ((access(shell->all_input->command_name, F_OK | X_OK)))
		&& !correct_dir(cmd_path, shell->cwd))
		return (2);
	else if (!cmd_path
		&& (access(shell->all_input->command_name, F_OK | X_OK) == 0)
		&& is_directory(shell->all_input->command_name, shell)
		&& (*shell->all_input->command_name == '.'
			|| *shell->all_input->command_name == '/'))
		return (7);
	else if (!cmd_path
		&& (access(shell->all_input->command_name, F_OK | X_OK) == 0)
		&& (*shell->all_input->command_name == '.'))
		return (3);
	else
		return (other_cases(cmd_path, shell));
}
