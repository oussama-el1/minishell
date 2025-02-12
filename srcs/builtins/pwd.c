/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:10:32 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/04 14:09:28 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_env *env)
{
	char	*cwd_from_env;
	char	*cwd_from_getcwd;

	cwd_from_getcwd = NULL;
	cwd_from_env = get_env_var(env, "PWD");
	if (!cwd_from_env)
	{
		cwd_from_getcwd = getcwd(NULL, 0);
		if (!cwd_from_getcwd)
		{
			perror("pwd");
			return (1);
		}
	}
	if (cwd_from_env)
		ft_putendl_fd(cwd_from_env, 1);
	else
		ft_putendl_fd(cwd_from_getcwd, 1);
	if (!cwd_from_env)
		free(cwd_from_getcwd);
	return (0);
}
