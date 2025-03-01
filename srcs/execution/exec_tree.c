/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:06:55 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/01 20:38:54 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	subshell_handler(t_tree *node, t_env *env, int *exit_status, pid_t pid)
{
	t_env	*env_cpy;
	int		status;
	int		saved_in;
	int		saved_out;
	int		exit_code;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (pid == 0)
	{
		env_cpy = dup_env(env);
		if (node->left)
		{
			if (node->args && node->args->redir)
				redirect_and_exec(node, env_cpy, *exit_status);
			exit_code = execute_ast(node->left, env_cpy, exit_status);
			free_env(env_cpy);
			clean_resources(saved_in, saved_out);
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

int	 execute_ast(t_tree *node, t_env *env, int *exit_status)
{
	int		left_status;
	pid_t	pid;

	if (!node)
	{
		*exit_status = 1;
		return (*exit_status);
	}
	setup_signals();
	if (node->args && node->args->argv && node->args->expand_list)
		argv_expander(node->args->argv, node->args->expand_list, env, *exit_status);
	if (node->type == T_CMD)
		*exit_status = redirect_and_exec(node, env, *exit_status);
	if (node->type == T_PIPE)
		*exit_status =  exec_pipe(node, env, exit_status);
	if (node->type == T_AND)
	{
		left_status = execute_ast(node->left, env, exit_status);
		if (left_status == 0)
			*exit_status =  execute_ast(node->right, env, exit_status);
		else
			*exit_status =  left_status;
	}
	if (node->type == T_OR)
	{
		left_status = execute_ast(node->left, env, exit_status);
		if (left_status != 0)
			*exit_status =  execute_ast(node->right, env, exit_status);
		else
			*exit_status = left_status;
	}
	if (node->type == T_SUBSHELL)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			*exit_status = 1;
		}
		else
			subshell_handler(node, env, exit_status, pid);
	}
	return (*exit_status);
}
