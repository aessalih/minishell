/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:13:42 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/31 21:57:04 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	handle_signal_for_bin(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	handle_quit_signal(int sig)
{
	(void)sig;
	write(2, "Quit: 3\n", 9);
}

static void	handle_signal_heredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	write(2, "\n", 1);
	g_signal = 1;
}

void	handle_all_signals(int mode)
{
	if (!mode)
	{
		signal(SIGINT, &handle_ctrl_c_for_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, &handle_ctrl_c_for_child);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
		signal(SIGINT, &handle_signal_heredoc);
	else if (mode == 3)
	{
		signal(SIGINT, &handle_signal_for_bin);
		signal(SIGQUIT, &handle_quit_signal);
	}
}
