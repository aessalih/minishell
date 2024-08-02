/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:18:48 by shamdoun          #+#    #+#             */
/*   Updated: 2024/08/02 14:20:51 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_all_env_vars(char **env, t_input *input)
{
	int	i;

	if (input->args && !empty_args(input->args))
	{
		ft_putstr_fd("env: ", 2);
		while (input->args && !input->args->arg)
			input->args = input->args->next;
		ft_putstr_fd(input->args->arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(WRONG_INPUT, 2);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strrchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

void	declare_all_envs(char **env)
{
	int		i;
	char	**split_env;

	i = 0;
	while (env[i])
	{
		split_env = ft_split_1(env[i], '=');
		if (ft_strncmp(split_env[0], "_", ft_strlen(split_env[0])))
		{
			printf("declare -x %s", split_env[0]);
			if (split_env[1])
				printf("=\"%s\"\n", split_env[1]);
			else if (ft_strchr(env[i], '='))
				printf("=\"\"\n");
			else
				printf("\n");
		}
		i++;
	}
}

int	env_exists(char *name, char **env)
{
	char	**split;

	while (*env)
	{
		split = ft_split_1(*env, '=');
		if (!ft_strncmp(split[0], name, ft_strlen(split[0]) + 1))
			return (1);
		env++;
	}
	return (0);
}

static char	*retrieve_value(t_shell *shell)
{
	char	*var;
	int		new_value;

	var = ft_getenv("SHLVL", shell->env);
	if (!var)
		return (NULL);
	new_value = ft_atoi(var, 0) + 1;
	if (new_value == 1000)
		return (ft_strdup(""));
	else if (new_value > 1000 || new_value == 256 && ft_strlen(var) > 4 && is_positive(var))
		return (ft_itoa_v2(1));
	else if (new_value <= 0 || new_value == 256 && ft_strlen(var) > 4 && !is_positive(var))
		return (ft_itoa_v2(0));
	else
		return (ft_itoa_v2(new_value));
}

void	update_shlvl(t_shell *shell)
{
	t_arg	*new_shlvl;
	char	*tmp;

	tmp = retrieve_value(shell);
	if (!tmp)
		return ;
	new_shlvl = ft_malloc(sizeof(t_arg), 0);
	if (!new_shlvl)
		return ;
	new_shlvl->arg = ft_strjoin("SHLVL=", tmp);
	new_shlvl->next = NULL;
	add_update_env(new_shlvl, shell, &shell->env, 0);
}
