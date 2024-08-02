/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:04:07 by shamdoun          #+#    #+#             */
/*   Updated: 2024/08/02 14:54:55 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_last_status(t_status *list)
{
	t_status	*head;

	if (g_signal == 2)
	{
		g_signal = 0;
		return (1);
	}
	head = list;
	if (!head)
		return (0);
	while (head->next)
		head = head->next;
	return (head->status);
}

void	exit_shell(t_shell *shell, t_arg *status, int mode)
{
	int	value;

	if (mode)
		write(1, "exit\n", 5);
	while (status && !status->arg)
		status = status->next;
	if (status)
	{
		value = ft_atoi(status->arg, 1);
		if (value == 255)
			(ft_malloc(0, -4), exit(255));
		if (status->next)
			return (error_status_update(EXCESS_ARGS, shell, 1));
		ft_malloc(0, -4);
		if (value == 258)
			value = 2;
		exit(value);
	}
	else
	{
		value = ft_last_status(shell->all_status);
		ft_malloc(0, -4);
		exit(value);
	}
}
