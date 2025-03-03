/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:16:05 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/03 00:18:52 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	change_home_dir(char **argv, t_env *env, int exit_status)
{
	char	*home;

	if (argv[1] == NULL)
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

static void	update_env(char *old_pwd, t_env *env)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_var(&env, ft_strdup("OLDPWD", ENV), ft_strdup(old_pwd, ENV), 1);
		set_env_var(&env, ft_strdup("PWD", ENV), ft_strdup(new_pwd, ENV), 1);
	}
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

int	ft_cd(char **argv, t_env *env, int exit_status)
{
	char		*old_pwd;
	int			home_res;
	const char	*oldpwd;

	old_pwd = get_env_var(env, "PWD", exit_status);
	home_res = change_home_dir(argv, env, exit_status);
	if (home_res == 1)
		return (1);
	if (home_res == 0)
		return (update_env(old_pwd, env), 0);
	if (argv[1] && !ft_strcmp(argv[1], "-"))
	{
		oldpwd = get_env_var(env, "OLDPWD", exit_status);
		if (chdir(oldpwd) == -1 && handle_oldpwd((char *)oldpwd))
			return (1);
		printf("%s\n", oldpwd);
	}
	else if (argv[1] && chdir(argv[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argv[1], 2);
		return (ft_putstr_fd(": No such file or directory\n", 2), 1);
	}
	update_env(old_pwd, env);
	return (0);
}
