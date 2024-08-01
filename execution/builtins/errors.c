/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:08:03 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/28 21:54:20 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_status_update(char *error, t_shell *shell, int s)
{
	if (error)
		ft_putstr_fd(error, 2);
	add_new_status(shell, s);
}

void	error_arg_status_update(char *error, char *arg, t_shell *shell, int s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
	add_new_status(shell, s);
}

void	fork_error(void)
{
	ft_putendl_fd("fork has failed!", 2);
	return ;
}

void	error_for_executables(char *cmd_name, t_shell *shell)
{
	if (ft_strchr(cmd_name, '/'))
		error_arg_status_update(NO_FILE_DIR, cmd_name, shell, 127);
	else
		error_arg_status_update(NO_COMMAND, cmd_name, shell, 127);
}

int	other_cases(char *cmd_path, t_shell *shell)
{
	if (!cmd_path
		&& (access(shell->all_input->command_name, F_OK | X_OK))
		&& (*shell->all_input->command_name == '.')
		&& is_file(shell->all_input->command_name, shell))
		return (2);
	else if (!cmd_path
		&& (access(shell->all_input->command_name, F_OK | X_OK) == 0)
		&& bin_exists(shell->all_input->command_name))
		return (2);
	else if (cmd_path && incorrect_syntax(cmd_path))
		return (6);
	return (0);
}
