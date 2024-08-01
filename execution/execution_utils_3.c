/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:59:21 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/24 21:03:32 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reorder_args(t_shell *shell)
{
	char	**test;
	int		i;

	i = 0;
	test = ft_split_1(shell->all_input->command_name, ' ');
	while (test && test[i])
		i++;
	if (i >= 1 && shell->is_expanded)
	{
		shell->all_input->command_name = test[0];
		while (--i > 0)
			ft_lstadd_front(&(shell->all_input->args), test[i]);
	}
}
