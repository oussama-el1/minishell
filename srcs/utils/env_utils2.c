/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:52:48 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/16 23:48:07 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_var(t_env **env, char *key,
		char *value, int exported)
{
	t_env	*new;
	t_env	*tmp;

	new = maroc(sizeof(t_env), ALLOC, ENV);
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->exported = exported;
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*init_env(char **environ)
{
	t_env	*env;
	int		i;
	char	*key;
	char	*value;
	char	*pwd;

	env = NULL;
	i = 0;
	if (!environ || !*environ)
	{
		pwd = getcwd(NULL, 0);
		add_env_var(&env, ft_strdup("PATH", ENV),
			ft_strdup("/usr/local/bin:/usr/bin:/bin", ENV), 1);
		add_env_var(&env, ft_strdup("PWD", ENV), ft_strdup(pwd, ENV), 1);
		add_env_var(&env, ft_strdup("_", ENV),
			ft_strdup("/usr/bin/env", ENV), 1);
		return (free(pwd), env);
	}
	while (environ[i])
	{
		set_name_and_value(environ[i], &key, &value);
		add_env_var(&env, key, value, 1);
		i++;
	}
	return (env);
}

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**get_env_array(t_env *env)
{
	char	**env_array;
	char	*temp;
	int		i;
	int		size;

	size = env_size(env);
	env_array = maroc(sizeof(char *) * (size + 1), ALLOC, CMD);
	if (!env_array)
		return (NULL);
	i = 0;
	while (i < size)
	{
		temp = ft_strjoin(ft_strdup(env->key, CMD), "=", CMD);
		env_array[i] = ft_strjoin(temp, env->value, CMD);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

t_env	*dup_env(t_env *original)
{
	t_env	*new_env;
	t_env	*current;

	new_env = NULL;
	current = original;
	while (current)
	{
		add_env_var(&new_env, ft_strdup(current->key, CMD),
			ft_strdup(current->value, CMD), current->exported);
		current = current->next;
	}
	return (new_env);
}
