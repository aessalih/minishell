/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:42:02 by shamdoun          #+#    #+#             */
/*   Updated: 2024/06/07 15:42:02 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokenize(t_input *token)
{
	while (token)
	{
		while (token->args)
		{
			free(token->args);
			token->args = token->args->next;
		}
		while (token->all_files)
		{
			free(token->all_files);
			token->all_files = token->all_files->next;
		}
		free(token->command_name);
		free(token);
	}
}
