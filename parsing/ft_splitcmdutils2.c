/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitcmdutils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:14:07 by aessalih          #+#    #+#             */
/*   Updated: 2024/08/04 14:59:53 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmdname(char *s, t_shell *shell)
{
	char	*ptr;
	char	*str;
	int		t;

	t = ft_isexpanded(s);
	ptr = NULL;
	str = NULL;
	if (t)
	{
		ptr = ft_expand(s, shell);
		shell->is_expanded = 1;
		return (ptr);
	}
	str = remove_quotes(s);
	return (str);
}

void	ft_createfile(char *name, t_shell *shell, char *str, t_file **new)
{
	char	*ptr;
	char	*s;
	size_t	t_f;

	t_f = ft_isexpanded(name);
	if (t_f)
		ptr = ft_expand(name, shell);
	else
		ptr = name;
	s = remove_quotes(ptr);
	if (!ft_strncmp(str, "<", 2))
		(*new) = ft_lstnew_file(s, 3, NULL);
	else if (!ft_strncmp(str, ">", 2))
		(*new) = ft_lstnew_file(s, 1, NULL);
	else if (!ft_strncmp(str, ">>", 3))
		(*new) = ft_lstnew_file(s, 2, NULL);
}
