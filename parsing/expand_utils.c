/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:09:31 by aessalih          #+#    #+#             */
/*   Updated: 2024/07/16 11:11:07 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlenex(char *cmd)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (cmd && cmd[i] && cmd[i] != '$')
	{
		(1) && (len++, i++);
	}
	return (len);
}

int	ft_isexpanded(char *str)
{
	char	*del;
	int		i;

	(1) && (i = 0, del = " \t'\".#!%%&()*+,-/:;<=>@[]\\^{}|~$");
	if (!ft_strncmp(str, "$", 2))
		return (0);
	while (str[i])
	{
		if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
				if (str[i] == '$' && str[i + 1] && !ft_strchr(del, str[i + 1]))
					return (1);
		}
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == '$' && str[i + 1] && !ft_strchr(del, str[i + 1]))
			return (1);
		if (str[i] == '$' && str[i + 1] && ft_strchr("\"'", str[i + 1]))
			return (1);
		if (str[i])
			i++;
	}
	return (0);
}

char	*ft_getname(char *str, t_shell *shell, int len)
{
	char	*ptr;
	char	*s;
	int		i;

	i = 1;
	if (str[i] == '?')
		return (ptr = ft_itoa(ft_last_status(shell->all_status)));
	if (str[i] >= '0' && str[i] <= '9')
		return (NULL);
	ptr = malloc(len + 1);
	while (len)
		(1) && (ptr[i - 1] = str[i], i++, --len);
	ptr[i - 1] = '\0';
	s = ft_getenv(ptr, shell->env);
	if (!s && !ft_strncmp(ptr, "PATH", 4))
		s = shell->r_path;
	if (s == NULL)
		return (free(ptr), NULL);
	i = 0;
	while (s && s[i])
		i++;
	(1) && (free(ptr), ptr = malloc(i + 1), i = 0);
	while (s && s[i])
		(1) && (ptr[i] = s[i], i++);
	return (ptr[i] = '\0', ptr);
}
