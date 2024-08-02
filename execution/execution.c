/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:57:57 by shamdoun          #+#    #+#             */
/*   Updated: 2024/08/01 17:08:48 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	run_options_path(t_shell *shell, char *command, int mode)
{
	if (!ft_strncmp(command, "env", 4))
	{
		update_env_path_var(shell, NULL, 1);
		if (print_all_env_vars(shell->env, shell->all_input))
			return ;
		add_new_status(shell, 0);
	}
	else if (!ft_strncmp(command, "pwd", 4))
		(printf("%s\n", shell->cwd), add_new_status(shell, 0));
	else if (!ft_strncmp(command, "cd", 3))
		change_directory(shell->all_input->args, shell, &shell->env);
	else if (!ft_strncmp(command, "export", 7))
		add_update_env(shell->all_input->args, shell, &shell->env, 1);
	else if (!ft_strncmp(command, "unset", 6))
		remove_env(shell->all_input->args, shell, &shell->env, 1);
	else if (!ft_strncmp(command, "echo", 5))
		echo_message(shell->all_input->args, shell);
	else if (!ft_strncmp(command, "exit", 5))
		exit_shell(shell, shell->all_input->args, mode);
	else
		execute_other_commands(shell, mode);
}

static void	run_options_no_path(t_shell *shell, char *command, int mode)
{
	if (!ft_strncmp(command, "pwd", 4))
		(printf("%s\n", shell->cwd), add_new_status(shell, 0));
	else if (!ft_strncmp(command, "cd", 3))
		change_directory(shell->all_input->args, shell, &shell->env);
	else if (!ft_strncmp(command, "export", 7))
		add_update_env(shell->all_input->args, shell, &shell->env, 1);
	else if (!ft_strncmp(command, "unset", 6))
		remove_env(shell->all_input->args, shell, &shell->env, 1);
	else if (!ft_strncmp(command, "echo", 5))
		echo_message(shell->all_input->args, shell);
	else if (!ft_strncmp(command, "exit", 5))
		exit_shell(shell, shell->all_input->args, mode);
	else
		execute_other_commands(shell, 1);
}

static void	run_options(t_shell *shell, char *command, int mode)
{
	char	*path_env;

	if (run_special_cases(shell, command))
		return ;
	path_env = ft_getenv("PATH", shell->env);
	if ((path_env && !shell->r_path) || (!path_env && shell->r_path))
		run_options_path(shell, command, mode);
	else
		run_options_no_path(shell, command, mode);
	if (mode)
		update_env_path_var(shell,
			ft_last_arg(command, shell->all_input->args), 0);
}

void	run_built_ins(t_shell *shell, int mode)
{
	update_args(shell);
	if (open_files(shell))
	{
		if (shell->all_input->in_file)
			close(shell->all_input->in_file);
		if (shell->all_input->out_file > 1)
			close(shell->all_input->out_file);
		return ;
	}
	if (redirect_streams(shell))
		return ;
	if (!shell->all_input->command_name)
	{
		close(shell->all_input->in_file);
		close(shell->all_input->out_file);
		return ;
	}
	run_options(shell, shell->all_input->command_name, mode);
	if (shell->all_input->in_file)
		close(shell->all_input->in_file);
	if (shell->all_input->out_file)
		close(shell->all_input->out_file);
	if (!mode)
		exit_shell(shell, NULL, 0);
}

void	execute_input(t_shell *shell)
{
	int	o_in;
	int	o_out;
	int	rv;

	o_in = dup(STDIN_FILENO);
	o_out = dup(STDOUT_FILENO);
	rv = handle_here_docs(shell);
	if (rv)
	{
		reset_resources(shell, rv, o_in, o_out);
		return ;
	}
	handle_all_signals(0);
	if (!shell->all_input->next)
		run_built_ins(shell, 1);
	else
		pipex(shell, 0);
	if (dup2(o_in, STDIN_FILENO) == -1)
		return ;
	if (dup2(o_out, STDOUT_FILENO) == -1)
		return ;
	close(o_in);
	close(o_out);
}
