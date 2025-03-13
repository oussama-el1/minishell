/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:26:48 by yslami            #+#    #+#             */
/*   Updated: 2025/03/13 20:41:18 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	contain_wild(char *str);

int	is_quote(enum e_token_type type)
{
	if (type == D_Q || type == S_Q)
		return (1);
	return (0);
}

int	is_regular(enum e_token_type type)
{
	if (type == EXPR || type == DOLLAR || is_quote(type))
		return (1);
	return (0);
}

void	is_wildcard(t_token *curr, bool *wild)
{
	if (curr && curr->type == EXPR && contain_wild(curr->value))
	{
		if (wild)
			*wild = true;
	}
}

static int	contain_wild(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

void	init_setup(t_helper *hp, t_env **env)
{
	g_exit_status = 0;
	hp->line_count = 0;
	hp->env = env;
}
