/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:40:37 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/13 20:48:34 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_and_cleanup(int *fd, pid_t left_cmd,
		pid_t right_cmd)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(left_cmd, &status, 0);
	waitpid(right_cmd, &status, 0);
	g_exit_status = WEXITSTATUS(status);
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
	execute_ast(hp);
	exit(g_exit_status);
}

static void	exec_pipe_helper(t_helper *hp, int *fd)
{
	pid_t	left_cmd;
	pid_t	right_cmd;
	t_tree	*parent;

	parent = hp->node;
	left_cmd = fork();
	if (left_cmd == -1)
	{
		g_exit_status = 1;
		return (perror("fork failed"), (void)0);
	}
	hp->node = parent->left;
	if (left_cmd == 0)
		exec_pipe_side(hp, fd, 1);
	right_cmd = fork();
	if (right_cmd == -1)
	{
		g_exit_status = 1;
		return (perror("fork failed"), (void)0);
	}
	hp->node = parent->right;
	if (right_cmd == 0)
		exec_pipe_side(hp, fd, 0);
	hp->node = parent;
	wait_and_cleanup(fd, left_cmd, right_cmd);
}

void	exec_pipe(t_helper *hp)
{
	int			fd[2];

	if (!hp->node || !hp->node->left || !hp->node->right)
		g_exit_status = 1;
	if (pipe(fd) == -1)
	{
		g_exit_status = 1;
		perror("pipe failed");
		return ;
	}
	exec_pipe_helper(hp, fd);
}
