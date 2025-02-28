/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:40:37 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/25 13:42:36 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	error_handler(char *message)
{
	perror(message);
	return (1);
}

static int	wait_and_cleanup(int *fd, pid_t left_cmd, pid_t right_cmd)
{
	close(fd[0]);
	close(fd[1]);
	waitpid(left_cmd, NULL, 0);
	waitpid(right_cmd, NULL, 0);
	return (0);
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

int	exec_pipe(t_tree *node, t_env *env, int *exit_status)
{
	int		fd[2];
	pid_t	left_cmd;
	pid_t	right_cmd;

	if (!node || !node->left || !node->right)
		return (1);
	if (pipe(fd) == -1)
		return (error_handler("pipe failed"));
	left_cmd = fork();
	if (left_cmd == -1)
		return (error_handler("fork failed"));
	if (left_cmd == 0)
	{
		exec_pipe_side(fd, 1);
		exit(execute_ast(node->left, env, exit_status));
	}
	right_cmd = fork();
	if (right_cmd == -1)
		return (error_handler("fork failed"));
	if (right_cmd == 0)
	{
		exec_pipe_side(fd, 0);
		exit(execute_ast(node->right, env, exit_status));
	}
	return (wait_and_cleanup(fd, left_cmd, right_cmd));
}
