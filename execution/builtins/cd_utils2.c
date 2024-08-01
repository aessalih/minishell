/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:25:13 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/15 17:26:02 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_same_value(char *p1, char *p2)
{
	char	*cp1;
	char	*cp2;

	cp1 = ft_strdup(p1);
	cp2 = ft_strdup(p2);
	ft_str_tolower(cp1);
	ft_str_tolower(cp2);
	if (!ft_strncmp(cp1, cp2, ft_strlen(cp1)))
		return (1);
	return (0);
}

int	check_path(t_arg *path, char *cwd)
{
	if (!path || !path->arg || !ft_strncmp(path->arg, "~", 2)
		|| !ft_strncmp(path->arg, "..", 3))
		return (1);
	if (ft_same_value(path->arg, cwd))
	{
		strcpy(cwd, path->arg);
		return (1);
	}
	return (0);
}

int	split_values(char ***split_cwd,
	char ***split_path, char *cwd, t_arg *path)
{
	*split_cwd = ft_split_1(cwd, '/');
	if (!(*split_cwd))
		return (1);
	*split_path = ft_split_1(path->arg, '/');
	if (path_is_only_levels(*split_path))
		return (1);
	if (!(*split_path))
		return (1);
	while ((!ft_strncmp((**split_path), ".", ft_strlen((**split_path)))
			|| !ft_strncmp((**split_path), "..", ft_strlen((**split_path)))))
		(*split_path)++;
	return (0);
}

int	copy_common_path(char **joined, char **split_cwd, char *delimeter)
{
	int		i;
	char	*tmp;

	i = 0;
	while (split_cwd[i] && !ft_same_value(split_cwd[i], delimeter))
	{
		*joined = ft_strjoin(*joined, split_cwd[i]);
		if (!(*joined))
			return (-1);
		tmp = *joined;
		*joined = ft_strjoin(*joined, "/");
		if (!(*joined))
			return (-1);
		i++;
	}
	return (i);
}

void	copy_unique_path(char **joined, char **split_cwd,
	char **split_path, int i)
{
	char	*tmp;

	update_cwd_list(split_cwd, split_path, i);
	while (split_cwd[i])
	{
		*joined = ft_strjoin(*joined, split_cwd[i]);
		if (!(*joined))
			return ;
		if (split_cwd[i + 1])
		{
			tmp = *joined;
			*joined = ft_strjoin(*joined, "/");
			if (!(*joined))
				return ;
		}
		i++;
	}
}
