/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:21:46 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/11 21:33:05 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subshell_worker(t_helper hp_cpy)
{
	int	red_res;
	int	exit_code;
	int	saved_in;
	int	saved_out;

	exit_code = 0;
	red_res = 0;
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (hp_cpy.node->left)
	{
		if (hp_cpy.node->args && hp_cpy.node->args->redir)
			red_res = redirect_and_exec(&hp_cpy);
		if (!red_res)
		{
			hp_cpy.node = hp_cpy.node->left;
			exit_code = execute_ast(&hp_cpy);
		}
		else
			exit_code = 1;
		clean_resources(&hp_cpy, saved_in, saved_out);
		exit(exit_code);
	}
	exit(0);
}

void	subshell_handler(t_helper *hp, pid_t pid)
{
	t_env		*env_cpy;
	t_helper	hp_cpy;
	int			status;

	env_cpy = dup_env(*hp->env);
	hp_cpy.exit_status = hp->exit_status;
	hp_cpy.env = &env_cpy;
	hp_cpy.node = hp->node;
	if (pid == 0)
		subshell_worker(hp_cpy);
	else
	{
		waitpid(pid, &status, 0);
		hp->exit_status = WEXITSTATUS(status);
	}
}
