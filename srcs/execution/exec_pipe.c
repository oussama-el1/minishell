/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:40:37 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/07 00:48:53 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_handler(char *message)
{
	perror(message);
	return (1);
}

static void	wait_and_cleanup(int *fd, pid_t left_cmd, pid_t right_cmd, int *exit_status)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(left_cmd, &status, 0);
	waitpid(right_cmd, &status, 0);
	*exit_status = WEXITSTATUS(status);
}

static void	exec_pipe_side(int *fd, int left)
{
	if (left)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	process_herdocs(t_tree *node, t_herdoc *herdoc, int left, t_env *env, int exit_status)
{
	herdoc->last_herdoc = NULL;
	if (node->left->args && left)
		herdoc->index = get_last_heredoc(node->left->args->redir, &herdoc->last_herdoc, exit_status, env);
	else if (node->right->args && !left)
		herdoc->index = get_last_heredoc(node->right->args->redir, &herdoc->last_herdoc, exit_status, env);
}

int	exec_pipe(t_tree *node, t_env **env, int *exit_status)
{
	int			fd[2];
	pid_t		left_cmd;
	pid_t		right_cmd;
	t_herdoc	*left_herdoc;
	t_herdoc	*right_herdoc;

	left_herdoc = NULL;
	right_herdoc = NULL;

	if (!node || !node->left || !node->right)
		return (1);

	if (pipe(fd) == -1)
		return (error_handler("pipe failed"));
	
	if (node->left->type == T_CMD)
	{
		left_herdoc = maroc(sizeof(t_herdoc), ALLOC, CMD);
		process_herdocs(node, left_herdoc, 1, *env, *exit_status);
	}

	if (node->right->type == T_CMD)
	{
		right_herdoc = maroc(sizeof(t_herdoc), ALLOC, CMD);
		process_herdocs(node, right_herdoc, 0, *env, *exit_status);
	}

	left_cmd = fork();
	if (left_cmd == -1)
		return (error_handler("fork failed"));
	if (left_cmd == 0)
	{
		exec_pipe_side(fd, 1);
		if (left_herdoc && left_herdoc->last_herdoc)
			exit(execute_ast(node->left, left_herdoc, env, exit_status));
		else
			exit(execute_ast(node->left, NULL, env, exit_status));
	}

	right_cmd = fork();
	if (right_cmd == -1)
		return (error_handler("fork failed"));
	if (right_cmd == 0)
	{
		exec_pipe_side(fd, 0);
		if (right_herdoc && right_herdoc->last_herdoc)
			exit(execute_ast(node->right, right_herdoc, env, exit_status));
		else
			exit(execute_ast(node->right, NULL, env, exit_status));
	}

	return (wait_and_cleanup(fd, left_cmd, right_cmd, exit_status), *exit_status);
}
