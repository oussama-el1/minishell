/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:12:37 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/03 17:32:22 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void expand_string(char **string, t_env *env, int exit_status)
{
	int		i = 0;
	int		start = 0;
	char	*expanded;
	char	*prefix;
	char	*key;
	char	*value;
	char	*temp;

	prefix = NULL;
	expanded = ft_strdup("", CMD);
	while ((*string)[i])
	{
		if ((*string)[i] == '$' && (*string)[i + 1] != '\0')
		{
			prefix = ft_substr(*string, start, i - start, CMD);
			temp = ft_strjoin(expanded, prefix, CMD);
			expanded = temp;
			key = extract_key(&(*string)[i + 1]);
			if (key[0] == '\0')
				temp = ft_strjoin(expanded, "$", CMD);
			else
			{
				value = get_env_var(env, key, exit_status);
				temp = ft_strjoin(expanded, value ? value : "", CMD);
			}
			expanded = temp;
			i += ft_strlen(key) + 1;
			start = i;
		}
		else
			i++;
	}

	if ((*string)[start])
	{
		temp = ft_strjoin(expanded, ft_strdup(&(*string)[start], CMD), CMD);
		expanded = temp;
	}
	*string = expanded;
}

void	expand_one_arg(char **argument, t_expand *curr, t_env *env, int exit_status)
{
	char		*new_arg;

	while (curr->next != NULL)
		curr = curr->next;
	new_arg = NULL;
	while (curr != NULL)
	{
		char *sub = ft_substr(*argument, curr->start, curr->end - curr->start, CMD);
		if (curr->expanded && ft_strchr(*argument, '$'))
			expand_string(&sub, env, exit_status);
		new_arg = ft_strjoin(sub, new_arg, CMD);
		curr = curr->prev;
	}
	*argument = new_arg;
}

void	argv_expander(char **argv, t_expand **expandArr, t_env *env, int exit_status)
{
	t_expand	*curr;
	int			i;

	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '$'))
		{
			curr = expandArr[i];
			expand_one_arg(&argv[i], curr, env, exit_status);
		}
		i++;
	}
}


