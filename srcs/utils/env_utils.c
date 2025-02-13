/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 23:46:35 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/13 08:04:52 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	add_env_var(t_env **env, char *key,
		char *value, int exported)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
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

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->exported)
		{
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
			else
				printf("%s=\n", env->key);
		}
		env = env->next;
	}
}

void	print_export(t_env *env, int declare)
{
	while (env)
	{
		if (declare)
			printf("declare -x ");
		if (env->value)
			printf("%s=\"%s\"\n", env->key, env->value);
		else
			printf("%s\n", env->key);
		env = env->next;
	}
}

int	unset_env_var(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

char	*get_env_var(t_env *env, char *key)
{
	if (ft_strcmp(key, "?") == 0)
        return (ft_itoa(g_exit_status));

	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_var(t_env **env, char *key, char *value, int exported)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			free(key);
			tmp->value = value;
			tmp->exported = exported;
			return ;
		}
		tmp = tmp->next;
	}
	add_env_var(env, key, value, exported);
}

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
		// PAATH=/usr/bin
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

int env_size(t_env *env)
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

char **get_env_array(t_env *env)
{
	char	**env_array;
	int		i;
	int		size;

	size = env_size(env);
	env_array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);

	i = 0;
	while (i < size)
	{
		char *temp = ft_strjoin_free(ft_strdup(env->key), "=");
		env_array[i] = ft_strjoin_free(temp, env->value);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

t_env	*dup_env(t_env *original)
{
    t_env *new_env = NULL;
    t_env *current = original;

    while (current)
    {
        add_env_var(&new_env, ft_strdup(current->key), ft_strdup(current->value), current->exported);
        current = current->next;
    }
    return new_env;
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
