/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:16:05 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/17 10:02:19 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	change_home_dir(char **argv, t_env *env, int force)
{
	char	*home;

	if (argv[1] == NULL || (!ft_strcmp(argv[1], "~") && !argv[2]) || force)
	{
		home = get_env_var(env, "HOME");
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		if (home[0] == '\0')
			return (0);
		if (chdir(home) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(home, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
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
		ft_putstr_fd("chdir: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		set_env_var(&env, ft_strdup("OLDPWD", ENV), ft_strdup(old_pwd, ENV), 1);
		change_home_dir(argv, env, 1);
		set_env_var(&env, ft_strdup("PWD", ENV),
			ft_strdup(get_env_var(env, "HOME"), ENV), 1);
		return (1);
	}
	set_env_var(&env, ft_strdup("OLDPWD", ENV), ft_strdup(old_pwd, ENV), 1);
	set_env_var(&env, ft_strdup("PWD", ENV), ft_strdup(new_pwd, ENV), 1);
	free(new_pwd);
	return (0);
}

static int	ft_cd_helper(char **argv)
{
	struct stat	path_stat;

	if (stat(argv[1], &path_stat) == 0 && !S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": Not a directory\n", 2);
		return (1);
	}
	if (chdir(argv[1]) == -1)
		return (print_cd_error(argv[1]), 1);
	return (0);
}

int	ft_cd(char **argv, t_env *env)
{
	char		*old_pwd;
	int			home_res;
	char		*oldpwd;

	old_pwd = get_env_var(env, "PWD");
	home_res = change_home_dir(argv, env, 0);
	if (home_res == 1)
		return (1);
	if (home_res == 0)
		return (update_env(argv, old_pwd, env), 0);
	if (argv[1] && !ft_strcmp(argv[1], "-"))
	{
		oldpwd = get_env_var(env, "OLDPWD");
		if (chdir(oldpwd) == -1)
			return (print_cd_error(oldpwd), 1);
		printf("%s\n", oldpwd);
	}
	else if (argv[1] && ft_cd_helper(argv))
		return (1);
	return (update_env(argv, old_pwd, env));
}
