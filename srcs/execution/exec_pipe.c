/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:40:37 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/08 23:18:10 by oel-hadr         ###   ########.fr       */
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

static void	pipe_executer(t_helper *hp, int *fd, t_herdoc *herdoc, int left)
{
	exec_pipe_side(fd, left);
	if (herdoc && herdoc->last_herdoc)
		exit(execute_ast(hp, herdoc));
	exit(execute_ast(hp, NULL));
}

static int	exec_pipe_helper(t_helper *hp, int *fd,
			t_herdoc *left_herdoc, t_herdoc *right_herdoc)
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
		pipe_executer(hp, fd, left_herdoc, 1);
	right_cmd = fork();
	if (right_cmd == -1)
		return (perror("fork failed"), 1);
	hp->node = parent->right;
	if (right_cmd == 0)
		pipe_executer(hp, fd, right_herdoc, 0);
	hp->node = parent;
	return (wait_and_cleanup(fd, left_cmd,
			right_cmd, &hp->exit_status), hp->exit_status);
}

int	exec_pipe(t_helper *hp)
{
	int			fd[2];
	t_herdoc	*left_herdoc;
	t_herdoc	*right_herdoc;

	left_herdoc = NULL;
	right_herdoc = NULL;
	if (!hp->node || !hp->node->left || !hp->node->right)
		return (1);
	if (pipe(fd) == -1)
		return (perror("pipe failed"), 1);
	if (hp->node->left->type == T_CMD)
	{
		left_herdoc = maroc(sizeof(t_herdoc), ALLOC, CMD);
		process_herdocs(hp, left_herdoc, 1);
	}
	if (hp->node->right->type == T_CMD)
	{
		right_herdoc = maroc(sizeof(t_herdoc), ALLOC, CMD);
		process_herdocs(hp, right_herdoc, 0);
	}
	return (exec_pipe_helper(hp, fd, left_herdoc, right_herdoc));
}
