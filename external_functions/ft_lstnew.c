/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:31:41 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/22 10:24:00 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_input	*ft_lstnew_input(void)
{
	t_input	*n_node;

	n_node = ft_malloc(sizeof(t_input), 0);
	if (!n_node)
		return (NULL);
	n_node->command_name = NULL;
	n_node->args = NULL;
	n_node->in_file = 0;
	n_node->out_file = 1;
	n_node->here_doc = 0;
	n_node->next = NULL;
	n_node->all_files = NULL;
	return (n_node);
}

t_a_data	*ft_lstnew_ad(void *address)
{
	t_a_data	*n_node;

	n_node = (t_a_data *)malloc(sizeof(t_a_data));
	if (!n_node)
		return (NULL);
	n_node->address = address;
	n_node->next = NULL;
	return (n_node);
}

t_status	*ft_lstnew_status(int status)
{
	t_status	*n_node;

	n_node = (t_status *)ft_malloc(sizeof(t_status), 0);
	if (!n_node)
		return (NULL);
	n_node->status = status;
	n_node->next = NULL;
	return (n_node);
}

t_file	*ft_lstnew_file(char *file_name, int type, char *delimeter)
{
	t_file	*n_node;

	n_node = (t_file *)ft_malloc(sizeof(t_file), 0);
	if (!n_node)
		return (NULL);
	n_node->file_name = file_name;
	n_node->delimeter = delimeter;
	n_node->type = type;
	n_node->hd_expand = 0;
	n_node->next = NULL;
	return (n_node);
}
