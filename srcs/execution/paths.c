/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:12:48 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/09 01:44:33 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ambiguous_redirect(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

static int	is_executable(char *path)
{
	struct stat	buf;

	if (!path)
		return (0);
	if (stat(path, &buf) != 0)
		return (0);
	if (S_ISDIR(buf.st_mode))
		return (0);
	return (access(path, X_OK) == 0);
}

static char	*find_binary_in_path_helper(char **dirs, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full_path = ft_strjoin(dirs[i], "/", CMD);
		full_path = ft_strjoin(full_path, cmd, CMD);
		if (is_executable(full_path))
			return (full_path);
		i++;
	}
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
	dirs = ft_split(secure_dirs, ':', CMD);
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
			return (ft_strdup(cmd, CMD));
		return (NULL);
	}
	return (find_binary_in_path(cmd, env, exit_status));
}
