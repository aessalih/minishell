/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:25:11 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/31 21:49:37 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_join_args(t_arg *args)
{
	char	*result;
	char	*tmp;

	result = NULL;
	result = ft_strdup(args->arg);
	if (!result)
		return (NULL);
	args = args->next;
	while (args)
	{
		if (args->arg)
		{
			tmp = ft_strjoin(" ", args->arg);
			if (!tmp)
				return (NULL);
			result = ft_strjoin(result, tmp);
			if (!result)
				return (NULL);
		}
		args = args->next;
	}
	return (result);
}

static int	is_flag(char *split)
{
	if (!split)
		return (0);
	if (*split == '-' && *(split + 1))
	{
		split++;
		while (*split)
		{
			if (*split != 'n')
				return (0);
			split++;
		}
		return (1);
	}
	return (0);
}

static void	print_message(t_arg *split, int *new_line)
{
	while (split && is_flag(split->arg))
	{
		*new_line = 0;
		split = split->next;
	}
	while (split)
	{
		if (split->arg)
		{
			ft_putstr_fd(split->arg, 1);
			if (split->next)
				ft_putstr_fd(" ", 1);
		}
		split = split->next;
	}
}

void	echo_message(t_arg *args, t_shell *shell)
{
	int	new_line;

	new_line = 1;
	if (!args)
	{
		printf("\n");
		add_new_status(shell, 0);
		return ;
	}
	print_message(args, &new_line);
	if (new_line)
		printf("\n");
	add_new_status(shell, 0);
}
