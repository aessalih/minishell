/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:58:50 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/22 10:24:04 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_allocated_data(t_a_data *list)
{
	t_a_data	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->address);
		tmp->address = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_all_collectors(t_a_data *l1, t_a_data *l2, t_a_data *l3)
{
	free_allocated_data(l1);
	free_allocated_data(l2);
	free_allocated_data(l3);
}

void	other_flags(int flag, t_a_data *garbage_collector
	, t_a_data *allocated_envs, t_a_data *important_addresses)
{
	if (flag == -1)
		free_allocated_data(garbage_collector);
	else if (flag == -2)
		free_allocated_data(allocated_envs);
	else if (flag == -3)
		free_allocated_data(important_addresses);
	else
		free_all_collectors(garbage_collector,
			allocated_envs, important_addresses);
}

void	*ft_malloc(size_t size, int flag)
{
	static t_a_data		*garbage_collector;
	static t_a_data		*allocated_envs;
	static t_a_data		*important_addresses;
	void				*address;

	if (!flag || flag > 0)
	{
		address = malloc(size);
		if (!address)
			return (NULL);
		if (!flag)
			add_a_data_to_linked_list(&important_addresses, address);
		else if (flag == 1)
			add_a_data_to_linked_list(&allocated_envs, address);
		else if (flag == 2)
			add_a_data_to_linked_list(&garbage_collector, address);
		return (address);
	}
	else
		other_flags(flag, garbage_collector,
			allocated_envs, important_addresses);
	return (NULL);
}
