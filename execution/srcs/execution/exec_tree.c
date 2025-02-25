/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:06:55 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/25 11:25:40 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	subshell_handler(t_tree *node, t_env *env, int *exit_status, pid_t pid, t_expand *expandArr)
{
	t_env	*env_cpy;
	int		status;

	if (pid == 0)
	{
		env_cpy = dup_env(env);
		if (node->left) 
		{
			int exit_code = execute_ast(node->left, env_cpy, exit_status, expandArr);
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

int	execute_ast(t_tree *node, t_env *env, int *exit_status, t_expand *expandArr)
{
	int		left_status;
	pid_t	pid;

	if (!node)
	{
		*exit_status = 1;
		return (*exit_status);
	}
	setup_signals();
	if (node->argv)
		argv_expander(node->argv, expandArr, env, *exit_status);
	if (node->type == CMD)
		*exit_status = exec_cmd(node, env, *exit_status);
	if (node->type == PIPE)
		*exit_status =  exec_pipe(node, env, exit_status, expandArr);
	if (node->type == AND)
	{
		left_status = execute_ast(node->left, env, exit_status, expandArr);
		if (left_status == 0)
			*exit_status =  execute_ast(node->right, env, exit_status, expandArr);
		*exit_status =  left_status;
	}
	if (node->type == OR)
	{
		left_status = execute_ast(node->left, env, exit_status, expandArr);
		if (left_status != 0)
			*exit_status =  execute_ast(node->right, env, exit_status, expandArr);
		else
			*exit_status = left_status;
	}
	if (node->type == SUBSHELL)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			*exit_status = 1;
		}
		else
			subshell_handler(node, env, exit_status, pid, expandArr);
	}
	return (*exit_status);
}
