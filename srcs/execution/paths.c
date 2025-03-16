/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:12:48 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/16 09:39:14 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ambiguous_redirect(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

int	is_executable(char *path)
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

static char	*find_binary_in_path(char *cmd, t_env *env)
{
	char	**dirs;
	char	*secure_dirs;

	secure_dirs = get_env_var(env, "PATH");
	if (!secure_dirs)
		return (NULL);
	dirs = ft_split(secure_dirs, ":", CMD);
	if (!dirs || !*dirs)
		return (NULL);
	return (find_binary_in_path_helper(dirs, cmd));
}

char	*get_executable_path(char *cmd, t_env *env)
{
	char	*path;

	path = find_binary_in_path(cmd, env);
	if (path)
		return (path);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')
		|| (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
	{
		if (is_executable(cmd))
			return (ft_strdup(cmd, CMD));
		return (NULL);
	}
	if (access(cmd, F_OK) == 0 && is_executable(cmd))
		return (ft_strdup(cmd, CMD));
	return (NULL);
}
