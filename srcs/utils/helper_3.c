/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:53:56 by yslami            #+#    #+#             */
/*   Updated: 2025/02/15 11:14:03 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	only_spaces(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (!is_space(str[i]))
			return (0);
	}
	return (1);
}

int	is_dilim(enum e_token_type type)
{
	if (type == PIPE || type == AND || type == OR)
		return (1);
	return (0);
}

int	isredirect(enum e_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND ||\
		type == HEREDOC)
		return (1);
	return (0);
}

int	contains_unquoted_ampersand(const char *str)
{
	int	single_q;
	int	double_q;
	int	i;

	single_q = 0;
	double_q = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (str[i] == '"' && !single_q)
			double_q = !double_q;
		else if (str[i] == '&' && !single_q && !double_q)
			return (1);
		i++;
	}
	return (0);
}
