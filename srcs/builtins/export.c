/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:25:02 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/11 02:48:52 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	validate_var_name(const char *var)
{
	int	i;

	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (0);
	i = 0;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	*getname(char *env, char *equal_ptr, int concat_flag)
{
	char	*name;

	name = NULL;
	if (equal_ptr)
	{
		name = malloc(sizeof(char) * (ft_strlen(env) - ft_strlen(equal_ptr)) + 1);
		if (!name)
			return (NULL);
		ft_strlcpy(name, env, ft_strlen(env) - ft_strlen(equal_ptr) + 1 - concat_flag);
	}
	return (name);
}

int	set_name_and_value(char *env, char **name, char **value)
{
	char	*equal_ptr;
	char	*concatination;
	int		concat_flag;

	concatination = ft_strchr(env, '+');
	concat_flag = (concatination && concatination[1] == '=');
	equal_ptr = ft_strchr(env, '=');
	if (equal_ptr)
	{
		*value = ft_strdup(equal_ptr + 1);
		*name = getname(env, equal_ptr, concat_flag);
	}
	else
	{
		*name = ft_strdup(env);
		*value = NULL;
	}
	return (concat_flag);
}

static int	process_env(char *env, t_env *env_ls)
{
	char	*name;
	char	*value;
	int		concat_flag;

	concat_flag = set_name_and_value(env, &name, &value);
	
	if (!validate_var_name(name))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(env, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(name);
		if (value)
			free(value);
		return (1);
	}
	if (value)
	{
		char *env_value = get_env_var(env_ls, name);
		if (concat_flag && env_value)
			set_env_var(&env_ls, name, ft_strjoin(env_value, value), 1);
		else
			set_env_var(&env_ls, name, value, 1);
	}
	else if (!get_env_var(env_ls, name))
		set_env_var(&env_ls, name, NULL, 0);
	return (0);
}

int	ft_export(char **argv, t_env *env)
{
	int	i;

	i = 1;
	if (!argv[1])
	{
		print_export(env, 1);
		return (0);
	}
	while (argv[i])
	{
		if (process_env(argv[i], env))
			return (1);
		i++;
	}
	return (0);
}

