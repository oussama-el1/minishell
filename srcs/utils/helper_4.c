/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:26:48 by yslami            #+#    #+#             */
/*   Updated: 2025/03/08 16:08:56 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_wild(char *str);

int	is_quote(enum e_token_type type)
{
	if (type == D_Q || type == S_Q)
		return (1);
	return (0);
}

int is_regular(enum e_token_type type)
{
	if (type == EXPR || type == DOLLAR || is_quote(type))
		return (1);
	return (0);
}

int	is_wildcard(t_token *curr)
{
	if (curr && (curr->bef_space || (!curr->bef_space && \
		!curr->prev)) && only_wild(curr->value))
		return (1);
	return (0);
}

static int	only_wild(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	if (isquote(*str))
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '*')
			count++;
		i++;
	}
	return (count != 0);
}

void	init_setup(t_helper *hp, t_env **env)
{
	hp->exit_status = 0;
	hp->env = env;
}
