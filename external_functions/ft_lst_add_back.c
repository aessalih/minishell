/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:31:35 by shamdoun          #+#    #+#             */
/*   Updated: 2024/06/07 15:40:15 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lst_add_input_back(t_input **lst, t_input *new, t_shell *shell)
{
	t_input	*head;

	(void)shell;
	head = (*lst);
	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

void	ft_lst_add_ad_back(t_a_data **lst, t_a_data *new)
{
	t_a_data	*head;

	if (!lst || !new)
		return ;
	head = *lst;
	if (!head)
		*lst = new;
	else
	{
		while (head -> next)
			head = head -> next;
		head -> next = new;
	}
}

void	ft_lst_add_file_back(t_file **lst, t_file *new, t_shell *shell)
{
	t_file	*head;

	(void)shell;
	if (!lst || !new)
		return ;
	head = *lst;
	if (!head)
		*lst = new;
	else
	{
		while (head -> next)
			head = head -> next;
		head -> next = new;
	}
}

void	ft_lst_add_status_back(t_status **lst, t_status *new, t_shell *shell)
{
	t_status	*head;

	(void)shell;
	if (!lst || !new)
		return ;
	head = *lst;
	if (!head)
		*lst = new;
	else
	{
		while (head -> next)
			head = head -> next;
		head -> next = new;
	}
}
