/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:06:55 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/10 04:16:06 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int execute_ast(t_tree *node, t_env *env)
{
	int		left_status;
	int		status;
	pid_t	pid;
	t_env	*env_cpy;


	if (!node)
	{
		g_exit_status = 1;
		return (1);
	}

	setup_signals();
	if (node->type == CMD)
		g_exit_status =  exec_command(node, env);

	if (node->type == REDIR_IN || node->type == REDIR_OUT || 
		node->type == REDIR_APPEND || node->type == HEREDOC)
		g_exit_status =  exec_redirection(node, env);

	if (node->type == PIPE)
		g_exit_status =  exec_pipe(node, env);

	if (node->type == AND)
	{
		left_status = execute_ast(node->left, env);
		if (left_status == 0)
			g_exit_status =  execute_ast(node->right, env);
		g_exit_status =  left_status;
	}

	if (node->type == OR)
	{
		left_status = execute_ast(node->left, env);
		if (left_status != 0)
			g_exit_status =  execute_ast(node->right, env);
		g_exit_status =  left_status;
	}

	if (node->type == SUBSHELL)
	{

		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			g_exit_status =  (1);
		}
		if (pid == 0)
		{
			env_cpy = dup_env(env);
			if (node->left) 
			{
				int exit_code = execute_ast(node->left, env_cpy);
				free_env(env_cpy);
				exit(exit_code);
			}
			free_env(env_cpy);
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			g_exit_status =  WEXITSTATUS(status);
		}
	}

	return (g_exit_status);
}
