/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:19:50 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/24 20:20:57 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	last_hd(t_shell *shell)
{
	t_file	*head;

	head = shell->all_input->all_files;
	if (head->type == 4 && !head->next
		&& (shell->all_input->in_file != shell->all_input->here_doc))
		return (1);
	while (head)
	{
		if (head->type == 4
			&& (shell->all_input->in_file == shell->all_input->here_doc))
			return (0);
		head = head->next;
	}
	return (1);
}
