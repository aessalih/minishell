/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:50:55 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/31 21:16:45 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hide_ctrl_c(void)
{
	struct termios	ter;

	if (tcgetattr(STDIN_FILENO, &ter) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	ter.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, 0, &ter) == -1)
		perror("tcsetattr");
}

void	ft_recover_echo(void)
{
	struct termios	ter;

	if (tcgetattr(STDIN_FILENO, &ter) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	ter.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, 0, &ter) == -1)
		perror("tcsetattr");
}

static int	init_shell_struct(t_shell **minishell, char **env)
{
	(*minishell) = ft_malloc(sizeof(t_shell), 0);
	if (!(*minishell))
		return (1);
	(*minishell)->all_allocated_data = NULL;
	(*minishell)->all_status = NULL;
	getcwd((*minishell)->cwd, sizeof((*minishell)->cwd));
	(*minishell)->all_input = NULL;
	(*minishell)->env = env;
	(*minishell)->r_path = NULL;
	return (0);
}

void	init_shell_environment(t_shell **minishell)
{
	char	*var;

	var = ft_getenv("PATH", (*minishell)->env);
	if (!var)
		(*minishell)->r_path
			= ft_strdup_v3("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0);
	if (!(*((*minishell)->env)))
		add_default_env(*minishell);
	else
		update_inhereted_env(*minishell);
	var = ft_getenv("_", (*minishell)->env);
	if (!var || ft_strncmp(var, "/usr/bin/env", 13))
		update_env_path_var(*minishell, NULL, 1);
	ft_hide_ctrl_c();
}

void	init(t_shell **minishell, char **env)
{
	if (init_shell_struct(minishell, env))
	{
		while (1)
			ft_putendl_fd(FAILED_MALLOC, 2);
	}
	init_shell_environment(minishell);
}
