/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:52:48 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/22 21:55:45 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*init_env(char **environ)
{
	t_env	*env;
	int		i;
	char	*key;
	char	*value;

	env = NULL;
	i = 0;
	while (environ[i])
	{
		set_name_and_value(environ[i], &key, &value);
		add_env_var(&env, key, value, 1);
		i++;
	}
	return (env);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
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
	env_array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (i < size)
	{
		temp = ft_strjoin_free(ft_strdup(env->key), "=");
		env_array[i] = ft_strjoin_free(temp, env->value);
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
		add_env_var(&new_env, ft_strdup(current->key),
			ft_strdup(current->value), current->exported);
		current = current->next;
	}
	return (new_env);
}
