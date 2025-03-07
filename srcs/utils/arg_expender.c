/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:12:37 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/05 02:34:33 by oel-hadr         ###   ########.fr       */
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

void expand_string(char **string, t_env *env, int exit_status, int fromherdoc)
{
	int		i;
	int		start ;
	char	*expanded;
	char	*prefix;
	char	*key;
	char	*value;
	char	*temp;

	start = 0;
	i = 0;
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
			else if (ft_isnum(key[0]))
				temp = ft_strjoin(expanded, &key[1], CMD);
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
	if ((*string)[0] == '$' && (*string)[1] == '\0' && !fromherdoc)
		expanded = *string;
	else if ((*string)[start])
	{
		temp = ft_strjoin(expanded, ft_strdup(&(*string)[start], CMD), CMD);
		expanded = temp;
	}
	*string = expanded;
}

int is_splited(t_expand *expand)
{
	while (expand)
	{
		if (expand->type != DOLLAR)
			return (0);
		expand = expand->next;
	}
	return (1);
}

char	**expand_one_arg(char *argument, t_expand *curr, t_env *env, int exit_status)
{
	char		*new_arg;
	char		**splitted;
	t_expand	*cp;

	cp = curr;
	while (curr->next)
		curr = curr->next;
	new_arg = NULL;
	while (curr)
	{
		char *sub = ft_substr(argument, curr->start, curr->end - curr->start, CMD);
		if (curr->expanded && ft_strchr(argument, '$'))
			expand_string(&sub, env, exit_status, 0);
		if (!ft_strcmp(sub, "$") && curr->next && (curr->type != curr->next->type && curr->next->type != EXPR))
			sub = NULL;
		new_arg = ft_strjoin(sub, new_arg, CMD);
		curr = curr->prev;
	}
	if (ft_strchr(new_arg, ' ') && !ft_strchr(new_arg, '=') && is_splited(cp))
		return (ft_split(new_arg, ' ', CMD));
	splitted = maroc(sizeof(char *) * 2, ALLOC, CMD);
	splitted[0] = new_arg;
	splitted[1] = NULL;
	return (splitted);
}

int	count_final_argument(char **argv, t_expand **expandArr, t_env *env, int exit_status)
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
			expanded_args = expand_one_arg(argv[i], expandArr[i], env, exit_status);
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

void	argv_expander(char ***argv, t_expand **expandArr, t_env *env, int exit_status)
{
	int		i;
	int		j;
	char	**new_argv;
	char	**return_arg;

	new_argv = maroc(sizeof(char *) * (count_final_argument(*argv, expandArr, env, exit_status) + 1), ALLOC, CMD);
	i = 0;
	j = 0;

	while ((*argv)[i])
	{
		if (ft_strchr((*argv)[i], '$'))
		{
			return_arg = expand_one_arg((*argv)[i], expandArr[i], env, exit_status);
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
