/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:37:31 by yslami            #+#    #+#             */
/*   Updated: 2025/02/16 10:33:34 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../../inc/minishell.h"

static void	expand_inside_quotes(char **str, t_env *env);

void	expand_variables(t_token *token, t_env *env)
{
	char	*value;

	while (token)
	{
		if (token->type == DOLLAR)
		{
			if (ft_isalpha(token->value[1]) || token->value[1] == '_')
			{
				value = get_env_var(env, token->value + 1);
				if (value)
					token->value = value;
				else
					token->value = ft_strdup("");
			}
			token->type = EXPR;
		}
		else if (token->type == D_Q)
			expand_inside_quotes(&token->value, env);
		token = token->next;
	}
}

static void	expand_inside_quotes(char **str, t_env *env)
{
	char	*expanded;
	char	*found;
	char	*var_value;
	char	*var_start;
	char	*var_name;
	int		i;

	expanded = *str;

	*str = expanded;
	while (is_found(&found, expanded))
	{
		var_start = found + 1;
		if (valid_dollar_var(var_start, &i))
		{
			var_name = ft_substr(var_start, 0, i);
			var_value = get_env_var(env, var_name);
			if (var_value)
				expanded = ft_strreplace(expanded, ft_strjoin("$", var_name), var_value);
			else
				var_value = ft_strdup("");
		}
		if (ft_strchr(expanded, '$'))
			expanded = ft_strchr(expanded, '$') + 1;
		else
			expanded += 1;
	}
	*str = expanded;
}

int	valid_dollar_var(const char *str, int *i)
{
	*i = 0;
	while (str[*i] && (is_alnum(str[*i]) || str[*i] == '_') && \
		!is_space(str[*i]) && !ft_isdigit(str[0]))
		*i++;
	return (*i);
}

int	is_found(char **found, char *str)
{
	*found = ft_strchr(str, '$');
	if (*found)
		return (1);
	else
		return (0);
}

char *find_replace(const char *str, const char *find, const char *replace)
{
	char *result, *ins, *tmp;
	int len_find, len_replace, len_front, count = 0;

	if (!str || !find)
		return (NULL);
	len_find = ft_strlen(find);
	if (!replace)
		replace = "";
	len_replace = ft_strlen(replace);

	// Count occurrences of 'find' in 'str'
	for (ins = (char *)str; (ins = ft_strstr(ins, find)); ins += len_find)
		count++;

	// Allocate memory for new string
	tmp = result = malloc(ft_strlen(str) + (len_replace - len_find) * count + 1);
	if (!result)
		return (NULL);

	while (count--)
	{
		ins = ft_strstr(str, find);
		len_front = ins - str;
		tmp = ft_memcpy(tmp, str, len_front) + len_front;
		tmp = ft_memcpy(tmp, replace, len_replace) + len_replace;
		str += len_front + len_find;
	}
	ft_strcpy(tmp, str);
	return (result);
}
*/
