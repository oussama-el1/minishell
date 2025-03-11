/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:40:37 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/11 20:17:48 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_and_cleanup(int *fd, pid_t left_cmd,
		pid_t right_cmd, int *exit_status)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(left_cmd, &status, 0);
	waitpid(right_cmd, &status, 0);
	*exit_status = WEXITSTATUS(status);
}

static void	exec_pipe_side(t_helper *hp, int *fd, int left)
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
	exit(execute_ast(hp));
}

static int	exec_pipe_helper(t_helper *hp, int *fd)
{
	pid_t	left_cmd;
	pid_t	right_cmd;
	t_tree	*parent;

	parent = hp->node;
	left_cmd = fork();
	if (left_cmd == -1)
		return (perror("fork failed"), 1);
	hp->node = parent->left;
	if (left_cmd == 0)
		exec_pipe_side(hp, fd, 1);
	right_cmd = fork();
	if (right_cmd == -1)
		return (perror("fork failed"), 1);
	hp->node = parent->right;
	if (right_cmd == 0)
		exec_pipe_side(hp, fd, 0);
	hp->node = parent;
	return (wait_and_cleanup(fd, left_cmd,
			right_cmd, &hp->exit_status), hp->exit_status);
}

int	exec_pipe(t_helper *hp)
{
	int			fd[2];

	if (!hp->node || !hp->node->left || !hp->node->right)
		return (1);
	if (pipe(fd) == -1)
		return (perror("pipe failed"), 1);
	return (exec_pipe_helper(hp, fd));
}
