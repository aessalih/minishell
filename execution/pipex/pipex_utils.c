/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:43:52 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/31 21:58:45 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	close_unused_here_docs(t_input *input)
{
	t_input	*head;

	head = input->next;
	while (head)
	{
		if (head->here_doc)
			close(head->here_doc);
		head = head->next;
	}
}

int	duplicate_ends(t_shell *shell, int *ends, int pipe_count, int i)
{
	int	j;

	if (i)
		if (dup2(ends[2 * i - 2], STDIN_FILENO) == -1)
			return (1);
	if (i != pipe_count)
		if (dup2(ends[2 * i + 1], STDOUT_FILENO) == -1)
			return (1);
	j = 0;
	while (j < pipe_count * 2)
	{
		close(ends[j]);
		j++;
	}
	close_unused_here_docs(shell->all_input);
	return (0);
}

static void	close_ends_and_wait(int pipe_count, int *ends,
	int *processes, t_shell *shell)
{
	int	j;
	int	status;

	j = 0;
	while (j < pipe_count * 2)
	{
		close(ends[j]);
		j++;
	}
	j = 0;
	while (j < pipe_count + 1)
	{
		waitpid(processes[j], &status, 0);
		if (WIFEXITED(status))
			add_new_status(shell, WEXITSTATUS(status));
		else
			add_new_status(shell, WTERMSIG(status) + 128);
		j++;
	}
}

void	release_fds(t_pipex *pipex, t_shell *shell, pid_t child, int i)
{
	pipex->processes[i] = child;
	close(shell->all_input->in_file);
	if (shell->all_input->here_doc)
		close(shell->all_input->here_doc);
}

void	post_pipe_update(t_pipex *pipex, t_shell *shell)
{
	close_ends_and_wait(pipex->pipe_count,
		pipex->ends, pipex->processes, shell);
	handle_all_signals(0);
	update_env_path_var(shell, NULL, 0);
}
