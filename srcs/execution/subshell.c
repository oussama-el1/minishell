/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:21:46 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/13 20:49:48 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subshell_worker(t_helper hp)
{
	int	red_res;
	int	saved_in;
	int	saved_out;

	red_res = 0;
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (hp.node->left)
	{
		if (hp.node->args && hp.node->args->redir)
			redirect_and_exec(&hp);
		if (!red_res)
		{
			hp.node = hp.node->left;
			execute_ast(&hp);
		}
		else
			g_exit_status = 1;
		clean_resources(&hp, saved_in, saved_out);
		exit(g_exit_status);
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
		g_exit_status = WEXITSTATUS(status);
	}
}
