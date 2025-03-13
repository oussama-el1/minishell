/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:12:37 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/13 02:43:24 by oel-hadr         ###   ########.fr       */
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

char	**expand_one_arg(char *argument, t_expand *curr, t_helper *hp)
{
	char		*sub;
	char		*new_arg;
	t_expand	*cp;

	cp = curr;
	while (curr->next)
		curr = curr->next;
	new_arg = NULL;
	while (curr)
	{
		sub = ft_substr(argument, curr->start,
				curr->end - curr->start, CMD);
		if (curr->expanded && ft_strchr(argument, '$'))
			expand_string(&sub, hp, 0);
		if (!ft_strcmp(sub, "$") && curr->next
			&& (curr->type != curr->next->type && curr->next->type != EXPR))
			sub = NULL;
		new_arg = ft_strjoin(sub, new_arg, CMD);
		curr = curr->prev;
	}
	return (split_arg(new_arg, cp, hp));
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
			expanded_args = expand_one_arg(argv[i],
					expandArr[i], hp);
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
		if (i == 0 && !ft_strcmp(new_argv[0], "export"))
			hp->export = 1;
		i++;
	}
	new_argv[j] = NULL;
	*argv = new_argv;
}
