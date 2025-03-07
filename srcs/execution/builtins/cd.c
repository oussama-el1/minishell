/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:16:05 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/04 21:01:22 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	change_home_dir(char **argv, t_env *env, int exit_status, int force)
{
	char	*home;

	if (argv[1] == NULL || (!ft_strcmp(argv[1], "~") && !argv[2]) || force)
	{
		home = get_env_var(env, "HOME", exit_status);
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		if (!*home)
			return (0);
		if (chdir(home) == -1)
		{
			perror("cd");
			return (1);
		}
		return (0);
	}
	return (-1);
}

static int	update_env(char **argv, char *old_pwd, t_env *env)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_putstr_fd("chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		set_env_var(&env, ft_strdup("OLDPWD", ENV), ft_strdup(old_pwd, ENV), 1);
		change_home_dir(argv, env, 0, 1);
		set_env_var(&env, ft_strdup("PWD", ENV), ft_strdup(get_env_var(env, "HOME", 0), ENV), 1);
		return (1);
	}
	set_env_var(&env, ft_strdup("OLDPWD", ENV), ft_strdup(old_pwd, ENV), 1);
	set_env_var(&env, ft_strdup("PWD", ENV), ft_strdup(new_pwd, ENV), 1);
	free(new_pwd);
	return (0);
}

int	handle_oldpwd(char *oldpwd)
{
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(oldpwd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

static void	print_cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (errno == ENOENT)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (errno == ENOTDIR)
		ft_putstr_fd(": Not a directory\n", 2);
	else if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", 2);
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}

int	ft_cd(char **argv, t_env *env, int exit_status)
{
	char		*old_pwd;
	int			home_res;
	char		*oldpwd;
	struct stat	path_stat;

	old_pwd = get_env_var(env, "PWD", exit_status);
	home_res = change_home_dir(argv, env, exit_status, 0);
	if (home_res == 1)
		return (1);
	if (home_res == 0)
		return (update_env(argv, old_pwd, env), 0);
	if (argv[1] && argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (argv[1] && !ft_strcmp(argv[1], "-"))
	{
		oldpwd = get_env_var(env, "OLDPWD", exit_status);
		if (chdir(oldpwd) == -1)
			return (print_cd_error(oldpwd), 1);
		printf("%s\n", oldpwd);
	}
	else if (argv[1])
	{
		if (stat(argv[1], &path_stat) == 0 && !S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": Not a directory\n", 2);
			return (1);
		}
		if (chdir(argv[1]) == -1)
			return (print_cd_error(argv[1]), 1);
	}
	return (update_env(argv, old_pwd, env));
}
