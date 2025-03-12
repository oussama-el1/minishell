/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:06:55 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/12 01:11:38 by oel-hadr         ###   ########.fr       */
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
	int		left_status;
	t_tree	*parent;

	parent = hp->node;
	hp->node = parent->left;
	left_status = execute_ast(hp);
	if (left_status == 0)
	{
		hp->node = parent->right;
		hp->exit_status = execute_ast(hp);
	}
	else
		hp->exit_status = left_status;
	hp->node = parent;
}

static void	exec_or(t_helper *hp)
{
	int		left_status;
	t_tree	*parent;

	parent = hp->node;
	hp->node = parent->left;
	left_status = execute_ast(hp);
	if (left_status != 0)
	{
		hp->node = parent->right;
		hp->exit_status = execute_ast(hp);
	}
	else
		hp->exit_status = left_status;
	hp->node = parent;
}

static int	expander(t_helper *hp)
{
	if (!hp->node)
	{
		hp->exit_status = 1;
		return (hp->exit_status);
	}
	if (hp->node->args && hp->node->args->argv && hp->node->args->expand_list)
	{
		hp->node->args->argv_cpy = hp->node->args->argv;
		hp->node->args->argv_cpy = hp->node->args->argv;
		argv_expander(&hp->node->args->argv, hp->node->args->expand_list, hp);
		if (contain_wildcard(hp->node->args->argv, hp->node->args->wildcards))
			expand_wildcard(&hp->node->args->argv, hp->node->args->wildcards);
	}
	return (0);
}

int	execute_ast(t_helper *hp)
{
	pid_t		pid;

	setup_signals();
	if (expander(hp))
		return (1);
	if (hp->node->type == T_CMD)
		hp->exit_status = redirect_and_exec(hp);
	if (hp->node->type == T_PIPE)
		hp->exit_status = exec_pipe(hp);
	if (hp->node->type == T_AND)
		exec_and(hp);
	if (hp->node->type == T_OR)
		exec_or(hp);
	if (hp->node->type == T_SUBSHELL)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			hp->exit_status = 1;
		}
		else
			subshell_handler(hp, pid);
	}
	return (hp->exit_status);
}
