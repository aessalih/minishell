/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:56:27 by shamdoun          #+#    #+#             */
/*   Updated: 2024/08/01 17:27:09 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_new_status(t_shell *shell, int status)
{
	t_status	*s;

	s = ft_malloc(sizeof(t_status), 0);
	if (!s)
		return ;
	s->status = status;
	s->next = NULL;
	ft_lst_add_status_back(&shell->all_status, s, shell);
	if (g_signal == 2)
		g_signal = 0;
}

static int	ft_array_size(char **list)
{
	int	n;

	n = 0;
	if (!list)
		return (n);
	while (list[n])
		n++;
	return (n);
}

int	ft_is_executable(char *cmd_path)
{
	char	**split_cmd_path;

	split_cmd_path = ft_split_1(cmd_path, '/');
	if (!split_cmd_path)
		return (2);
	if (!split_cmd_path[1]
		&& !ft_strncmp(split_cmd_path[1], "minishell",
			ft_strlen(split_cmd_path[1])))
		return (1);
	else if (!ft_strncmp(split_cmd_path[ft_array_size(split_cmd_path) - 1],
			"minishell",
			ft_strlen(split_cmd_path[ft_array_size(split_cmd_path) - 1])))
		return (1);
	return (0);
}

int	list_len(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

void	update_list_value(char *data, char *old_list_value, char **new_environ)
{
	if (!ft_strchr(old_list_value, '='))
		old_list_value = ft_strjoin(old_list_value, "=");
	if (append_mode(data))
		data = ft_strjoin(old_list_value,
				ft_strchr_occurence(data, '=') + 1);
	else
		data = ft_strdup(data);
	if (!data)
		return ;
	ft_memcpy(new_environ, &data, sizeof(char *));
}
