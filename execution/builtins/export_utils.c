/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:38:11 by shamdoun          #+#    #+#             */
/*   Updated: 2024/08/01 08:44:36 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	empty_args(t_arg *data)
{
	while (data)
	{
		if (data->arg)
			return (0);
		data = data->next;
	}
	return (1);
}

int	unset_syntax_error(char *data)
{
	int	i;

	i = 0;
	if (data[i] != '_' && !ft_isalpha(data[i]))
		return (1);
	i++;
	while (data[i] && data[i + 1])
	{
		if (data[i] != '_' && ((!ft_isalpha(data[i]) && !ft_isdigit(data[i]))
				|| data[i] == '\''))
			return (1);
		i++;
	}
	if (data[i] && data[i] != '_'
		&& (data[i] == '\'' || data[i] == '=' || (!ft_isalpha(data[i])
				&& !ft_isdigit(data[i]))))
		return (1);
	return (0);
}

int	export_syntax_error(char *data)
{
	int	i;

	i = 0;
	if (data[i] != '_' && !ft_isalpha(data[i]))
		return (1);
	i++;
	if (data[i] == '=')
		return (0);
	while (data[i] && data[i + 1] && data[i + 1] != '=')
	{
		if ((data[i] != '_' && (!ft_isalpha(data[i]) && !ft_isdigit(data[i])))
			|| (data[i] == '\''))
			return (1);
		i++;
	}
	if (data[i])
	{
		if (data[i] == '+' && data[i + 1] == '=')
			return (0);
		else if (((data[i] == '+' && data[i + 1] != '=') || data[i] == '\'')
			|| (data[i] != '_' && !ft_isalpha(data[i]) && !ft_isdigit(data[i])))
			return (1);
	}
	return (0);
}

int	check_args(t_arg *data, t_shell *shell, char ***env)
{
	if (!data || empty_args(data))
	{
		(declare_all_envs(*env), add_new_status(shell, 0));
		return (1);
	}
	return (0);
}

void	split_var(char ***split_env, t_arg *data, t_shell *shell)
{
	if (append_mode(data->arg))
		*split_env = ft_split_1(data->arg, '+');
	else
		*split_env = ft_split_1(data->arg, '=');
	if (!(*split_env))
	{
		add_new_status(shell, 1);
		return ;
	}
}
