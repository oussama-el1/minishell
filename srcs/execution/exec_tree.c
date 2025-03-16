/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:06:55 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/16 09:05:54 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_herdocs(t_helper *hp)
{
	t_tree	*parent;

	if (!hp->node)
		return ;
	if (hp->node->args && hp->node->type == T_CMD)
		herdoc_runner(hp->node->args->redir, hp);
	if (hp->node->type == T_SUBSHELL)
	{
		parent = hp->node;
		hp->node = parent->left;
		execute_herdocs(hp);
		hp->node = parent;
		if (hp->node->args)
			herdoc_runner(hp->node->args->redir, hp);
	}
	if (hp->node->type == T_PIPE
		|| hp->node->type == T_AND || hp->node->type == T_OR)
	{
		parent = hp->node;
		hp->node = parent->left;
		execute_herdocs(hp);
		hp->node = parent->right;
		execute_herdocs(hp);
		hp->node = parent;
	}
}

static void	exec_and(t_helper *hp)
{
	t_tree	*parent;

	parent = hp->node;
	hp->node = parent->left;
	execute_ast(hp);
	if (g_signals.exit_status == 0)
	{
		hp->node = parent->right;
		execute_ast(hp);
	}
	hp->node = parent;
}

static void	exec_or(t_helper *hp)
{
	t_tree	*parent;

	parent = hp->node;
	hp->node = parent->left;
	execute_ast(hp);
	if (g_signals.exit_status != 0)
	{
		hp->node = parent->right;
		execute_ast(hp);
	}
	hp->node = parent;
}

static void	expander(t_helper *hp)
{
	if (hp->node->args && hp->node->args->argv && hp->node->args->expand_list)
	{
		hp->node->args->argv_cpy = hp->node->args->argv;
		hp->node->args->argv_cpy = hp->node->args->argv;
		argv_expander(&hp->node->args->argv, hp->node->args->expand_list, hp);
		if (contain_wildcard(hp->node->args->argv, hp->node->args->wildcards))
			expand_wildcard(hp);
	}
}

static void	sighandler_exec(int sig)
{
	if (sig == SIGINT)
		g_signals.sigint_child = CTRL_C;
	if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", 1);
		g_signals.sigint_child = QUIT;
	}
}

void	execute_ast(t_helper *hp)
{
	pid_t		pid;

	signal(SIGQUIT, sighandler_exec);
	signal(SIGINT, sighandler_exec);
	if (!hp->node)
		return ;
	expander(hp);
	if (hp->node->type == T_CMD)
		redirect_and_exec(hp);
	if (hp->node->type == T_PIPE)
		exec_pipe(hp);
	if (hp->node->type == T_AND)
		exec_and(hp);
	if (hp->node->type == T_OR)
		exec_or(hp);
	if (hp->node->type == T_SUBSHELL)
	{
		pid = fork();
		if (pid == -1)
			(perror("fork failed"), g_signals.exit_status = 1);
		else
			subshell_handler(hp, pid);
	}
	if (g_signals.sigint_child)
	{
		g_signals.exit_status = g_signals.sigint_child;
		g_signals.sigint_child = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &hp->term);
	}
}
