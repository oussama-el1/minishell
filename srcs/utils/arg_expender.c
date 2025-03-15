/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:12:37 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/15 07:29:09 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *str)
{
	int		i;
	char	*key;

	if (!str || !str[0])
		return (NULL);
	if (str[0] == '?')
		return (ft_strdup("?", CMD));
	i = 0;
	while (str[i] && (ft_is_alnum(str[i]) || str[i] == '_'))
		i++;
	key = ft_substr(str, 0, i, CMD);
	return (key);
}

static char	**process_sub(char *sub, t_expand *curr, int count, char **final_args)
{
	char **splitted;

	if (curr->type == S_Q || curr->type == D_Q)
	{
		splitted = maroc(sizeof(char *) * 2, ALLOC, CMD);
		splitted[0] = sub;
		splitted[1] = NULL;
	}
	else if (curr->type == DOLLAR && ft_strchr(sub, ' '))
		splitted = ft_split(sub, ' ', CMD);
	else
	{
		splitted = maroc(sizeof(char *) * 2, ALLOC, CMD);
		splitted[0] = sub;
		splitted[1] = NULL;
	}
	if (curr->type == EXPR && count > 0)
	{
		if (final_args[0])
			final_args[0] = ft_strjoin(sub, final_args[0], CMD);
		splitted = NULL;
	}
	return splitted;
}


void	process_splitted(char **final_args, char **splitted,
			t_expand *curr, int *count)
{
	int	i;
	int	j;

	i = -1;
	while (splitted[++i])
		*count += 1;
	if (curr->next && curr->next->type == EXPR)
	{
		if (splitted[i - 1])
		{
			i--;
			*count -= 1;
			splitted[i] = ft_strjoin(splitted[i], final_args[0], CMD);
		}
		final_args[0] = splitted[i];
	}
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

char	**expand_one_arg(char *argument, t_expand *curr, t_helper *hp)
{
	char	*sub;
	char	**splitted;
	char	**final_args;
	int		count;

	while (curr->next)
		curr = curr->next;
	final_args = maroc(sizeof(char *) * 100, ALLOC, CMD);
	count = 0;
	while (curr)
	{
		sub = ft_substr(argument, curr->start, curr->end - curr->start, CMD);
		if (curr->expanded && ft_strchr(argument, '$'))
			expand_string(&sub, hp, 0);
		if (!ft_strcmp(sub, "$") && curr->next && curr->type != curr->next->type && curr->next->type != EXPR)
			sub = NULL;
		splitted = process_sub(sub, curr, count, final_args);
		if (splitted)
			process_splitted(final_args, splitted, curr, &count);
		curr = curr->prev;
	}
	final_args[count] = NULL;
	return (final_args);
}

int	count_final_argument(char **argv, t_expand **expandArr, t_helper *hp)
{
	int		i;
	int		count;
	char	**expanded_args;
	int		k;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '$'))
		{
			expanded_args = expand_one_arg(argv[i], expandArr[i], hp);
			k = 0;
			while (expanded_args[k])
			{
				count++;
				k++;
			}
		}
		else
			count++;
		i++;
	}
	return (count);
}

void	argv_expander(char ***argv, t_expand **expandArr, t_helper *hp)
{
	int		i;
	int		j;
	char	**new_argv;
	char	**return_arg;

	new_argv = maroc(sizeof(char *) * (count_final_argument(*argv,
					expandArr, hp) + 1), ALLOC, CMD);
	i = 0;
	j = 0;
	while ((*argv)[i])
	{
		if (ft_strchr((*argv)[i], '$'))
		{
			return_arg = expand_one_arg((*argv)[i], expandArr[i], hp);
			while (*return_arg)
				new_argv[j++] = *return_arg++;
		}
		else
			new_argv[j++] = (*argv)[i];
		i++;
	}
	new_argv[j] = NULL;
	*argv = new_argv;
}
