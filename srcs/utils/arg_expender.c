/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:12:37 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/16 09:23:06 by yslami           ###   ########.fr       */
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

char	**expand_one_arg(char *argument, t_expand *curr, t_helper *hp, int *len)
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
		if (!ft_strcmp(sub, "$") && curr->next && curr->type != curr->next->type && curr->next->type != EXPR && curr->next->type == DOLLAR)
			sub = NULL;
		if (sub)
			splitted = process_sub(sub, curr, count, final_args);
		else
			splitted = NULL;
		if (splitted)
			process_splitted(final_args, splitted, curr, &count);
		curr = curr->prev;
	}
	final_args[count] = NULL;
	*len += count;
	return (final_args);
}

int	count_final_argument(char **argv, t_expand **expandArr, t_helper *hp)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '$'))
			expand_one_arg(argv[i], expandArr[i], hp, &count);
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
	int		k;
	int		count;
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
			count = 0;
			return_arg = expand_one_arg((*argv)[i], expandArr[i], hp, &count);
			k = 0;
			while (k < count)
			{
				new_argv[j++] = *return_arg++;
				k++;
			}
		}
		else
			new_argv[j++] = (*argv)[i];
		i++;
	}
	new_argv[j] = NULL;
	*argv = new_argv;
}
