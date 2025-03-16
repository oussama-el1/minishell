/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:45:38 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/16 08:20:48 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**handle_splitting(char *sub, t_expand *curr)
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
	return (splitted);
}

char	**process_sub(char *sub, t_expand *curr, int count, char **final_args)
{
	char	**splitted;
	int		i;

	splitted = handle_splitting(sub, curr);
	if (!splitted || count == 0 || !final_args[0])
		return (splitted);
	if (curr->type == S_Q || curr->type == D_Q || curr->type == EXPR)
	{
		final_args[0] = ft_strjoin(splitted[0], final_args[0], CMD);
		splitted = NULL;
	}
	else if (curr->type == DOLLAR)
	{
		i = 0;
		while (splitted[i])
			i++;
		final_args[0] = ft_strjoin(splitted[i - 1], final_args[0], CMD);
		splitted[i - 1] = NULL;
	}
	return (splitted);
}

void	process_splitted(char **final_args, char **splitted,
		t_expand *curr, int *count)
{
	int	i;
	int	j;

	i = -1;
	while (splitted[++i])
		(*count)++;
	(void)curr;
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
