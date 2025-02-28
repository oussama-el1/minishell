/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:16:05 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/22 21:28:18 by oel-hadr         ###   ########.fr       */
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
		set_env_var(&env, ft_strdup("OLDPWD"), ft_strdup(old_pwd), 1);
		set_env_var(&env, ft_strdup("PWD"), ft_strdup(new_pwd), 1);
		free(new_pwd);
	}
}

int	ft_cd(char **argv, t_env *env, int exit_status)
{
	char	*old_pwd;
	int		home_res;

	old_pwd = get_env_var(env, "PWD", exit_status);
	home_res = change_home_dir(argv, env, exit_status);
	if (home_res == 1)
		return (1);
	if (home_res == 0)
	{
		update_env(old_pwd, env);
		return (0);
	}
	if (argv[1] && chdir(argv[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	update_env(old_pwd, env);
	return (0);
}
