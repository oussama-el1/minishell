/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:21:46 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/17 09:25:06 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subshell_worker(t_helper hp)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (hp.node->left)
	{
		if (hp.node->args && hp.node->args->redir)
			redirect_and_exec(&hp);
		if (g_signals.exit_status != 1)
		{
			hp.node = hp.node->left;
			execute_ast(&hp);
		}
		clean_resources(saved_in, saved_out);
		exit(g_signals.exit_status);
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
		g_signals.exit_status = WEXITSTATUS(status);
	}
}
