/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 03:58:04 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/17 10:51:50 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	**env_to_array(t_env *env)
{
	int		i;
	int		count;
	char	**env_arr;
	char	*entry;

	count = env_count(env);
	env_arr = maroc(sizeof(char *) * (count + 1), ALLOC, CMD);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			entry = ft_strjoin(env->key, ft_strjoin("=\"",
						env->value, CMD), CMD);
			entry = ft_strjoin(entry, "\"", CMD);
		}
		else
			entry = ft_strdup(env->key, CMD);
		env_arr[i++] = entry;
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

static void	bubble_sort(char **arr, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(t_env *env, int declare)
{
	char	**env_arr;
	int		count;
	int		i;

	count = env_count(env);
	env_arr = env_to_array(env);
	bubble_sort(env_arr, count);
	i = 0;
	while (env_arr[i])
	{
		if (declare)
			printf("declare -x %s\n", env_arr[i]);
		else
			printf("%s\n", env_arr[i]);
		i++;
	}
}
