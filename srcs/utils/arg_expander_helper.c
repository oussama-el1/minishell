/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expander_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:33:21 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/12 06:04:49 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_remaining(char **string, char *expanded,
		int start, int fromherdoc)
{
	char	*temp;

	if ((*string)[0] == '$' && (*string)[1] == '\0' && !fromherdoc)
		expanded = *string;
	else if ((*string)[start])
	{
		temp = ft_strjoin(expanded, ft_strdup(&(*string)[start], CMD), CMD);
		expanded = temp;
	}
	*string = expanded;
}

static void	expand_key(t_helper *hp, char **string, char **expanded, int *i)
{
	char	*key;
	char	*value;
	char	*temp;

	key = extract_key(&(*string)[*i + 1]);
	if (key[0] == '\0')
		temp = ft_strjoin(*expanded, "$", CMD);
	else if (ft_isnum(key[0]))
		temp = ft_strjoin(*expanded, &key[1], CMD);
	else
	{
		value = get_env_var(*hp->env, key, hp->exit_status);
		if (value)
			temp = ft_strjoin(*expanded, value, CMD);
		else
			temp = ft_strjoin(*expanded, "", CMD);
	}
	*expanded = temp;
	*i += ft_strlen(key) + 1;
}

void	expand_string(char **string, t_helper *hp, int fromherdoc)
{
	int		i;
	int		start;
	char	*expanded;
	char	*prefix;

	start = 0;
	i = 0;
	expanded = ft_strdup("", CMD);
	while ((*string)[i])
	{
		if ((*string)[i] == '$' && (*string)[i + 1] != '\0')
		{
			prefix = ft_substr(*string, start, i - start, CMD);
			expanded = ft_strjoin(expanded, prefix, CMD);
			expand_key(hp, string, &expanded, &i);
			start = i;
		}
		else
			i++;
	}
	process_remaining(string, expanded, start, fromherdoc);
}
