/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:06:55 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/16 15:56:14 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_ast(t_tree *node, t_env *env, int *exit_status)
{
	int		left_status;
	int		status;
	pid_t	pid;
	t_env	*env_cpy;


	if (!node)
	{
		*exit_status = 1;
		return (*exit_status);
	}

	setup_signals();

	if (node->type == CMD)
		*exit_status = exec_cmd(node, env, *exit_status);

	if (node->type == PIPE)
		*exit_status =  exec_pipe(node, env, exit_status);

	if (node->type == AND)
	{
		left_status = execute_ast(node->left, env, exit_status);
		if (left_status == 0)
			*exit_status =  execute_ast(node->right, env, exit_status);
		*exit_status =  left_status;
	}

	if (node->type == OR)
	{
		left_status = execute_ast(node->left, env, exit_status);
		if (left_status != 0)
			*exit_status =  execute_ast(node->right, env, exit_status);
		else
			*exit_status = left_status;
	}

	if (node->type == SUBSHELL)
	{

		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			*exit_status =  (1);
		}
		if (pid == 0)
		{
			env_cpy = dup_env(env);
			if (node->left) 
			{
				int exit_code = execute_ast(node->left, env_cpy, exit_status);
				free_env(env_cpy);
				exit(exit_code);
			}
			free_env(env_cpy);
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			*exit_status =  WEXITSTATUS(status);
		}
	}

	return (*exit_status);
}


/*

cat < input.txt > EOF << output.txt

[file1, file2, file3, NULL]

*/