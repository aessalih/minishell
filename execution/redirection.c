/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:06:03 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/31 21:06:09 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_here_doc_fd(int *fd, t_input *input)
{
	*fd = open("here_doc.txt", O_CREAT | O_TRUNC | O_WRONLY, 777);
	if (*fd < 0)
	{
		perror("failed to open here_doc file for writing");
		return (1);
	}
	input->here_doc = open("here_doc.txt", O_RDONLY, 777);
	if (input->here_doc < 0)
	{
		perror("failed to open here_doc file!");
		return (1);
	}
	(unlink("here_doc.txt"), ft_hide_ctrl_c());
	return (0);
}

static int	here_doc(t_input *input, t_file *file, t_shell *shell)
{
	char	*line;
	int		fd;

	if (open_here_doc_fd(&fd, input))
		return (1);
	handle_all_signals(2);
	line = NULL;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || (ft_strlen(line) - 1 == ft_strlen(file->delimeter)
				&& !ft_strncmp(line, file->delimeter, ft_strlen(line) - 1)))
			break ;
		if (line && file->hd_expand)
			line = ft_expand_hd(line, shell);
		(write(fd, line, ft_strlen(line)));
	}
	close(fd);
	if (g_signal == 1)
		return (1);
	ft_recover_echo();
	return (0);
}

int	handle_here_docs(t_shell *shell)
{
	t_input	*i_head;
	t_file	*f_head;
	int		hd_rv;

	i_head = shell->all_input;
	while (i_head)
	{
		f_head = i_head->all_files;
		while (f_head)
		{
			if (f_head->type == 4)
			{
				if (i_head->here_doc)
					close(i_head->here_doc);
				hd_rv = here_doc(i_head, f_head, shell);
				if (hd_rv)
					return (hd_rv);
				else
					add_new_status(shell, 0);
			}
			f_head = f_head->next;
		}
		i_head = i_head->next;
	}
	return (0);
}

int	open_input_files(t_shell *shell)
{
	if (shell->all_input->in_file && last_hd(shell))
		close(shell->all_input->in_file);
	if (shell->all_input->all_files->type == 3)
		shell->all_input->in_file
			= open(shell->all_input->all_files->file_name, O_RDONLY);
	if (shell->all_input->all_files->type == 4
		&& (!shell->all_input->command_name
			|| !ft_strncmp("cat", shell->all_input->command_name, 3)))
		shell->all_input->in_file = shell->all_input->here_doc;
	if (shell->all_input->in_file < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(shell->all_input->all_files->file_name, 2);
		ft_putendl_fd(": No such file or directory", 2);
		add_new_status(shell, 1);
		return (1);
	}
	return (0);
}

int	redirect_streams(t_shell *shell)
{
	if (shell->all_input->in_file > 0)
		if (dup2(shell->all_input->in_file, STDIN_FILENO) == -1)
			add_new_status(shell, 1);
	if (shell->all_input->out_file > 1)
		if (dup2(shell->all_input->out_file, STDOUT_FILENO) == -1)
			add_new_status(shell, 1);
	if (shell->all_input->here_doc)
		close(shell->all_input->here_doc);
	return (0);
}
