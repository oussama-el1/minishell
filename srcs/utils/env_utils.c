/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 23:46:35 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/05 22:41:11 by oel-hadr         ###   ########.fr       */
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
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

char	*get_env_var(t_env *env, char *key, int exit_status)
{
	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(exit_status, CMD));
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
			tmp->value = value;
			tmp->exported = exported;
			return ;
		}
		tmp = tmp->next;
	}
	add_env_var(env, key, value, exported);
}
