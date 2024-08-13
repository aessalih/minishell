/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:10:36 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/31 21:13:38 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cmds(t_commands *cmd)
{
	t_commands	*head;
	char		**str;
	int			i;

	head = cmd;
	while (head)
	{
		i = 0;
		str = ft_split(head->command);
		while (str[i])
		{
			if ((!ft_strncmp(str[i], "<<", ft_strlen(str[i]))
					|| !ft_strncmp(str[i], ">>", ft_strlen(str[i])))
				&& str[i + 1] && (!ft_strncmp(str[i + 1],
						"<<", ft_strlen(str[i + 1]))
					|| !ft_strncmp(str[i + 1], ">>", ft_strlen(str[i + 1]))))
				return (free_list(cmd), ft_free_split(str), 1);
			i++;
		}
		ft_free_split(str);
		head = head->next;
	}
	return (0);
}

static void	ft_start(char *input, t_shell *minishell)
{
	t_commands	*cmds;
	int			check;

	cmds = create_cmd(input);
	if (cmds == NULL)
	{
		perror("allocation failed...");
		return ;
	}
	add_space(cmds);
	check = check_cmds(cmds);
	if (check)
		(add_new_status(minishell, 258), perror("syntax error\n"));
	else
	{
		minishell->all_input = split_cmd(cmds, minishell);
		if (!minishell->all_input)
		{
			(perror("syntax error\n"),
				add_new_status(minishell, 258));
			return ;
		}
		(ft_recover_echo(),
			execute_input(minishell), ft_hide_ctrl_c());
	}
}

static void	check_execute(char *input, t_shell *minishell)
{
	int			check;

	check = ft_parsing(input);
	if (check)
		ft_start(input, minishell);
	else
	{
		add_new_status(minishell, 258);
		perror("syntax error\n");
	}
	add_history(input);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_shell		*minishell;

	(void)argc;
	(void)argv;
	minishell = NULL;
	init(&minishell, env);
	handle_all_signals(0);
	ft_reset_terminal(0);
	while (1)
	{
		input = readline("minishell$> ");
		if (!input)
			exit_shell(minishell, NULL, 1);
		if (*input != '\0')
			check_execute(input, minishell);
		free(input);
		ft_reset_terminal(1);
	}
	return (1);
}
