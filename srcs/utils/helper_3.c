/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:53:56 by yslami            #+#    #+#             */
/*   Updated: 2025/03/12 04:31:31 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty(char *str)
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
	if (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND || \
		type == HEREDOC)
		return (1);
	return (0);
}

int	non_control(enum e_token_type type)
{
	if (!is_dilim(type) && !isredirect(type))
		return (1);
	return (0);
}

int	islogical(enum e_token_type type)
{
	if (type == AND || type == OR)
		return (1);
	return (0);
}
