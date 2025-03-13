/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:21:46 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/13 04:38:11 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subshell_worker(t_helper hp)
{
	int	red_res;
	int	exit_code;
	int	saved_in;
	int	saved_out;

	exit_code = 0;
	red_res = 0;
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (hp.node->left)
	{
		if (hp.node->args && hp.node->args->redir)
			red_res = redirect_and_exec(&hp);
		if (!red_res)
		{
			hp.node = hp.node->left;
			exit_code = execute_ast(&hp);
		}
		else
			exit_code = 1;
		clean_resources(&hp, saved_in, saved_out);
		exit(exit_code);
	}
	exit(0);
}

void	subshell_handler(t_helper *hp, pid_t pid)
{
	int	status;

	if (pid == 0)
		subshell_worker(*hp);
	else
	{
		waitpid(pid, &status, 0);
		hp->exit_status = WEXITSTATUS(status);
	}
}
