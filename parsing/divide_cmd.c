/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:13:38 by aessalih          #+#    #+#             */
/*   Updated: 2024/07/31 21:20:49 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_commands	*create_commands(t_commands *list, char *content)
{
	t_commands	*new;
	t_commands	*head;

	head = list;
	new = malloc(sizeof(t_commands));
	if (new == NULL)
		return (free_list(list), NULL);
	new->command = content;
	new->next = NULL;
	if (list == NULL)
	{
		list = new;
		return (list);
	}
	while (list->next)
		list = list->next;
	list->next = new;
	return (head);
}

static int	cmd_lenght(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '|')
		i++;
	return (i);
}

static char	*ft_mediator(char *cmd, char *input, int *j)
{
	char	q;

	q = *input;
	cmd[*j] = *input;
	(*j)++;
	input++;
	while (*input != q)
	{
		cmd[*j] = *input;
		input++;
		(*j)++;
	}
	return (input);
}

t_commands	*create_cmd(char *input)
{
	t_var		v;
	t_commands	*cmd_list;

	cmd_list = NULL;
	while (*input)
	{
		v.j = 0;
		v.cmd = malloc((sizeof(char) * cmd_lenght(input)) + 1);
		if (v.cmd == NULL)
			return (NULL);
		while (*input && *input != '|')
		{
			if (*input == '\'' || *input == '"')
				input = ft_mediator(v.cmd, input, &v.j);
			v.cmd[v.j] = *input;
			(1) && (v.j++, input++);
		}
		v.cmd[v.j] = '\0';
		cmd_list = create_commands(cmd_list, v.cmd);
		if (cmd_list == NULL)
			return (NULL);
		if (*input)
			input++;
	}
	return (cmd_list);
}
