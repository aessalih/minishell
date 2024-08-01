/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:12:16 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/31 21:08:48 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	create_pipes(int **ends, int count)
{
	int	i;

	*ends = malloc(sizeof(int) * 2 * count);
	if (!(*ends))
		return (1);
	i = 0;
	while (i < count)
	{
		if (pipe((*ends) + 2 * i))
			return (1);
		i++;
	}
	return (0);
}

static int	count_nbr_of_pipes(t_input *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i - 1);
}

static int	init_pipex(t_pipex **pipex, t_shell *shell)
{
	*pipex = ft_malloc(sizeof(t_pipex), 2);
	if (!(*pipex))
		return (1);
	(*pipex)->pipe_count = count_nbr_of_pipes(shell->all_input);
	if (create_pipes(&(*pipex)->ends, (*pipex)->pipe_count))
		return (1);
	(*pipex)->processes = ft_malloc(sizeof(int)
			* ((*pipex)->pipe_count + 1), 2);
	if (!(*pipex)->processes)
		return (1);
	return (0);
}

static void	run_child(t_shell *shell, t_pipex *pipex, int i, int mode)
{
	add_new_status(shell, 0);
	if (duplicate_ends(shell, pipex->ends, pipex->pipe_count, i))
		exit (1);
	(run_built_ins(shell, mode), exit(ft_last_status(shell->all_status)));
}

void	pipex(t_shell *shell, int mode)
{
	t_pipex	*pipex;
	pid_t	child;
	int		i;

	if (init_pipex(&pipex, shell))
		return ;
	i = 0;
	handle_all_signals(3);
	while (i < pipex->pipe_count + 1)
	{
		child = fork();
		if (child < 0)
		{
			add_new_status(shell, 1);
			return (fork_error());
		}
		if (!child)
			run_child(shell, pipex, i, mode);
		release_fds(pipex, shell, child, i);
		shell->all_input = shell->all_input->next;
		i++;
	}
	post_pipe_update(pipex, shell);
}
