/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:15:58 by aessalih          #+#    #+#             */
/*   Updated: 2024/08/01 15:49:00 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_redirection(t_input *nw, char *str, char *name, t_shell *shell)
{
	t_file	*new;
	size_t	t_f;
	char	*ptr;
	char	*s;

	(1) && (new = NULL, ptr = NULL, s = NULL, t_f = 0);
	if (!strncmp(str, "<", 2) || !strncmp(str, ">", 2)
		|| !strncmp(str, ">>", 3))
	{
		ft_createfile(name, shell, str, &new);
	}
	else if (!strncmp(str, "<<", 3))
	{
		ptr = cut_exp(name);
		ptr = remove_quotes(ptr);
		new = ft_lstnew_file(NULL, 4, ptr);
		if (ft_strlen(name) == ft_strlen(ptr))
			new->hd_expand = 1;
	}
	if (!new)
		return ;
	ft_lst_add_file_back(&(nw->all_files), new, shell);
}

static t_arg	*put_arg(t_arg *arguments, char *str, t_shell *shell)
{
	t_arg	*new;
	t_arg	*head;
	char	*ptr;

	head = arguments;
	ptr = NULL;
	new = ft_malloc(sizeof(t_arg), 0);
	if (!new)
		return (NULL);
	new->t_f = ft_isexpanded(str);
	if (new->t_f)
		ptr = ft_expand(str, shell);
	else
		ptr = str;
	new->arg = remove_quotes(ptr);
	new->next = NULL;
	if (!arguments)
	{
		arguments = new;
		return (arguments);
	}
	while (head->next)
		head = head->next;
	head->next = new;
	return (arguments);
}

static int	check_last(char *str)
{
	if (!strncmp(str, ">", 2))
		return (0);
	else if (!strncmp(str, "<", 2))
		return (0);
	else if (!strncmp(str, ">>", 3))
		return (0);
	else if (!strncmp(str, "<<", 3))
		return (0);
	return (1);
}

static int	filltoken(t_commands *cmd, t_input *new, t_shell *shell)
{
	char	**str;
	int		i;
	int		t;

	str = ft_split(cmd->command);
	(1) && (i = 0, t = 0);
	while (str[i])
		i++;
	if (i - 1 >= 0 && !check_last(str[i - 1]))
		return (ft_free_split(str), 0);
	i = 0;
	while (str[i])
	{
		if (str[i][0] == '<' || str[i][0] == '>')
		{
			put_redirection(new, str[i], str[i + 1], shell);
			i++;
		}
		else if (t == 0)
			(1) && (t = 1, new->command_name = get_cmdname(str[i], shell));
		else
			(new)->args = put_arg((new)->args, str[i], shell);
		i++;
	}
	return (free_array(str), 1);
}

t_input	*split_cmd(t_commands *cmd, t_shell *shell)
{
	t_commands	*head;
	t_input		*tokenize;
	t_input		*new;
	int			check;

	tokenize = NULL;
	head = cmd;
	shell->is_expanded = 0;
	while (cmd)
	{
		new = ft_lstnew_input();
		if (!new)
			return (NULL);
		check = filltoken(cmd, new, shell);
		if (!check)
			return (free_tokenize(tokenize), free_list(head), NULL);
		ft_lst_add_input_back(&tokenize, new, shell);
		cmd = cmd->next;
	}
	free_list(head);
	return (tokenize);
}
