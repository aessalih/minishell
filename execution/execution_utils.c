/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:39:56 by shamdoun          #+#    #+#             */
/*   Updated: 2024/08/03 20:22:19 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_resources(t_shell *shell, int rv, int o_in, int o_out)
{
	add_new_status(shell, rv);
	g_signal = 0;
	handle_all_signals(0);
	dup2(o_in, STDIN_FILENO);
	dup2(o_out, STDOUT_FILENO);
	close(o_in);
	close(o_out);
	while (shell->all_input)
	{
		if (shell->all_input->here_doc)
			close(shell->all_input->here_doc);
		shell->all_input = shell->all_input->next;
	}
}

static int	open_output_files(t_shell *shell)
{
	if (shell->all_input->out_file > 1)
		close(shell->all_input->out_file);
	if (shell->all_input->all_files->type == 1)
		shell->all_input->out_file
			= open(shell->all_input->all_files->file_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (shell->all_input->all_files->type == 2)
		shell->all_input->out_file
			= open(shell->all_input->all_files->file_name,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (shell->all_input->out_file < 0)
	{
		perror("failed to open output file!");
		add_new_status(shell, 1);
		return (1);
	}
	return (0);
}

int	open_files(t_shell *shell)
{
	while (shell->all_input->all_files)
	{
		if (shell->all_input->all_files->type != 4 && ambiguous_redirect(shell))
			return (1);
		if (shell->all_input->all_files->type >= 3 && open_input_files(shell))
			return (1);
		if (shell->all_input->all_files->type < 3 && open_output_files(shell))
			return (1);
		shell->all_input->all_files = shell->all_input->all_files->next;
	}
	return (0);
}

int	run_special_cases(t_shell *shell, char *command)
{
	if (!ft_strncmp(command, ".", 2)
		&& (!shell->all_input->args || empty_args(shell->all_input->args)))
	{
		ft_putendl_fd(POINT_INPUT, 2);
		add_new_status(shell, 2);
		return (1);
	}
	else if (!ft_strncmp(command, ".", 2))
	{
		ft_putendl_fd("minishell: .: No such file or directoty", 2);
		add_new_status(shell, 1);
		return (1);
	}
	else if (!ft_strncmp(command, "..", 2))
	{
		error_arg_status_update(NO_COMMAND, command, shell, 127);
		return (1);
	}
	return (0);
}

void	update_args(t_shell *shell)
{
	t_arg	*head;

	head = shell->all_input->args;
	if (!shell->all_input->command_name && shell->all_input->args)
	{
		while (head)
		{
			if (head->arg)
			{
				shell->all_input->command_name = head->arg;
				head->arg = NULL;
				break ;
			}
			head = head->next;
		}
	}
	reorder_args(shell);
}
