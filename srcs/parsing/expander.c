/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:37:31 by yslami            #+#    #+#             */
/*   Updated: 2025/02/15 19:50:48 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// "Y $HOME me me $NAME42" => "Y /home/ me me "

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
		if (!valid_dollar_var(var_start, &i))
		{}
		if (ft_strchr(expanded, '$'))
			expanded = ft_strchr(expanded, '$') + 1;
		else
			expanded += 1;
	}
}

/*
static void	expand_inside_quotes(char **str, t_env *env)
{
	char	*expanded;
	char	*found;
	char	*var_value;
	char	*var_start;
	char	*var_name;
	int		i;

	expanded = *str;

	while (is_found(&found, expanded))
	{
		var_start = found + 1;  // Start looking after the $
		if (ft_isalpha(*var_start) || *var_start == '_')  // Check if it's a valid variable name
		{
			// Find the variable name in the environment
			if (valid_dollar_var(var_start, &i))
			{
				var_name = ft_substr(var_start, 0, i);
				var_value = get_env_var(env, var_name);
				if (var_value)
					expanded = ft_strreplace(expanded, ft_strjoin("$", var_name), var_value);
				else
					var_value = ft_strdup("");
			}
		}
		// Move to the next part of the string
		expanded = ft_strchr(expanded, '$') ? ft_strchr(expanded, '$') + 1 : expanded + 1;
	}
	*str = expanded;
}
*/


int	valid_dollar_var(const char *str, int *i)
{
	*i = 0;
	while (str[*i] && (is_alnum(str[*i]) || str[*i] == '_'))
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


// "hello my name is /home/jscbhsb/ $HOME" // echo "$34234_HELLO"

/* this function should be in string_helper */
// char	*find_replace(const char *str, const char *find, \
// 		const char *replace)
// {
// 	if (!str || !find)
// 		return (NULL);
// 	if (!replace)
// 		replace = "";
// }


/*


static void	expand_inside_quotes(char **str, t_env *env)
{
	char	*expanded;
	char	*found;
	char	*var_value;
	char	*var_start;
	char	*var_name;

	expanded = *str;
	while ((found = ft_strchr(expanded, '$'))) // Find '$' in the string
	{
		var_start = found + 1; // Move past '$'

		// Extract variable name (only alphanumeric and '_')
		int i = 0;
		while (var_start[i] && (ft_isalnum(var_start[i]) || var_start[i] == '_'))
			i++;

		if (i == 0) // If "$" is not followed by a valid name, skip it
		{
			expanded = found + 1;
			continue;
		}

		// Allocate memory for variable name
		var_name = ft_substr(var_start, 0, i);
		if (!var_name)
			return ; // Handle allocation failure

		// Fetch value from env list
		var_value = get_env_var(env, var_name);
		free(var_name); // Free after use

		// Replace "$VAR_NAME" with its value (or empty string if not found)
		expanded = find_replace(expanded, found, var_value ? var_value : "");
	}

	*str = expanded; // Assign back the expanded string
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

/*
	// the condition in expand_variables()
	if (token->type == D_Q)
	{
		int	count = search_expend_dollar(token->value);
		if (!coun)
			break ;
		token->value = expnad_inside_quotes(token->value, count, env);
	}


	expnad_inside_quotes(const char *str, int count, t_env *env)
	{
		int	i;

		i = -1;
		while (str[++i])
		{
			if ()
		}
	}
*/


/*
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
