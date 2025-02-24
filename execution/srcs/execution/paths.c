/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:12:48 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/23 13:17:43 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_executable(char *path)
{
	if (!path)
		return (0);
	return (access(path, X_OK) == 0);
}

static void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*find_binary_in_path_helper(char **dirs, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full_path = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin_free(full_path, cmd);
		if (is_executable(full_path))
		{
			free_str_array(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_str_array(dirs);
	return (NULL);
}

static char	*find_binary_in_path(char *cmd, t_env *env, int exit_status)
{
	char	**dirs;
	char	*secure_dirs;

	secure_dirs = get_env_var(env, "PATH", exit_status);
	if (!secure_dirs)
	{
		ft_putendl_fd("$PATH var not found", 2);
		return (NULL);
	}
	dirs = ft_split(secure_dirs, ':');
	if (!dirs || !*dirs)
	{
		ft_putendl_fd("No secure directory found", 2);
		return (NULL);
	}
	return (find_binary_in_path_helper(dirs, cmd));
}

char	*get_executable_path(char *cmd, t_env *env, int exit_status)
{
	if (cmd[0] == '/' || ((cmd[0] == '.' && cmd[1] == '/')
			|| (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')))
	{
		if (is_executable(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (find_binary_in_path(cmd, env, exit_status));
}
