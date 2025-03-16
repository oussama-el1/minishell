/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:45:38 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/16 07:13:28 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**process_sub(char *sub, t_expand *curr,
	int count, char **final_args)
{
	char	**splitted;

	if (curr->type == S_Q || curr->type == D_Q)
	{
		splitted = maroc(sizeof(char *) * 2, ALLOC, CMD);
		splitted[0] = sub;
		splitted[1] = NULL;
	}
	else if (curr->type == DOLLAR && !ft_strcmp(sub, ""))
		return (NULL);
	else if (curr->type == DOLLAR)
		splitted = ft_split(sub, " \t\n\v\f\r", CMD);
	else
	{
		splitted = maroc(sizeof(char *) * 2, ALLOC, CMD);
		splitted[0] = sub;
		splitted[1] = NULL;
	}
	if (count > 0)
	{
		if (final_args[0])
			final_args[0] = ft_strjoin(splitted[0], final_args[0], CMD);
		splitted = NULL;
	}
	return (splitted);
}

static void	handle_expr_join(char **final_args,
		char **splitted, int *i, int *count)
{
	if (splitted[*i - 1])
	{
		(*i)--;
		(*count)--;
		splitted[*i] = ft_strjoin(splitted[*i], final_args[0], CMD);
	}
	final_args[0] = splitted[*i];
}

void	process_splitted(char **final_args, char **splitted,
		t_expand *curr, int *count)
{
	int	i;
	int	j;

	i = -1;
	while (splitted[++i])
		(*count)++;

	if (curr->next && curr->next->type == EXPR)
		handle_expr_join(final_args, splitted, &i, count);
	j = *count - 1;
	while (j >= i)
	{
		final_args[j] = final_args[j - i];
		j--;
	}
	j = 0;
	while (j < i)
	{
		final_args[j] = splitted[j];
		j++;
	}
}
