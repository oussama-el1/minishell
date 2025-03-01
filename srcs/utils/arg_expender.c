/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:12:37 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/28 23:54:58 by yslami           ###   ########.fr       */
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
		return (ft_strdup("?"));
	i = 0;
	while (str[i] && (ft_is_alnum(str[i]) || str[i] == '_'))
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}

void expand_string(char **string, t_env *env, int exit_status)
{
	int		i = 0;
	int		start = 0;
	char	*expanded = ft_strdup("");
	char	*prefix;
	char	*key;
	char	*value;
	char	*temp;

	prefix = NULL;
	while ((*string)[i])
	{
		if ((*string)[i] == '$' && (*string)[i + 1] != '\0')
		{
			prefix = ft_substr(*string, start, i - start);
			temp = ft_strjoin(expanded, prefix);
			free(prefix);
			expanded = temp;

			key = extract_key(&(*string)[i + 1]);
			if (key[0] == '\0')
				temp = ft_strjoin(expanded, "$");
			else
			{
				value = get_env_var(env, key, exit_status);
				temp = ft_strjoin(expanded, value ? value : "");
			}
			free(expanded);
			expanded = temp;

			i += ft_strlen(key) + 1;
			start = i;
			free(key);
		}
		else
			i++;
	}

	if ((*string)[start])
	{
		temp = ft_strjoin(expanded, ft_strdup(&(*string)[start]));
		expanded = temp;
	}
	*string = expanded;
}

// void	argv_expander(char **argv, t_expand *expandArr, t_env *env, int exit_status)
// {
// 	int		i;
// 	int		expanded_idx;
// 	int		save;
// 	int		stop;
// 	int		len;
// 	char	*new_arg;

// 	i = 0;
// 	expanded_idx = 0;
// 	while (argv[i])
// 	{
// 		if (ft_strchr(argv[i], '$'))
// 		{
// 			stop = expanded_idx;
// 			len = ft_strlen(argv[i]);
// 			while (expandArr[expanded_idx].end != (unsigned int)len)
// 				expanded_idx++;
// 			save = expanded_idx;
// 			new_arg = NULL;
// 			while (expanded_idx >= stop)
// 			{
// 				char *sub = ft_substr(argv[i], expandArr[expanded_idx].start, expandArr[expanded_idx].end - expandArr[expanded_idx].start);
// 				if (expandArr[expanded_idx].expanded && ft_strchr(argv[i], '$'))
// 					expand_string(&sub, env, exit_status);
// 				new_arg = ft_strjoin(sub, new_arg);
// 				expanded_idx--;
// 			}
// 			argv[i] = new_arg;
// 			expanded_idx = save;
// 		}
// 		expanded_idx++;
// 		i++;
// 	}
// }

void	argv_expander(char **argv, t_expand **expandArr, t_env *env, int exit_status)
{
	int		i;
	char	*new_arg;
	t_expand *curr;

	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '$'))
		{
			curr = expandArr[i];
			while (curr->next != NULL)
				curr = curr->next;
			new_arg = NULL;
			while (curr != NULL)
			{
				char *sub = ft_substr(argv[i], curr->start, curr->end - curr->start);
				if (curr->expanded && ft_strchr(argv[i], '$'))
					expand_string(&sub, env, exit_status);
				new_arg = ft_strjoin(sub, new_arg);
				curr = curr->prev;
			}
			argv[i] = new_arg;
		}
		i++;
	}
}
