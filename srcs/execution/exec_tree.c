/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:06:55 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/10 22:17:28 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	subshell_worker(t_helper hp_cpy)
{
	int	red_res;
	int	exit_code;
	int	saved_in;
	int	saved_out;

	exit_code = 0;
	red_res = 0;
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (hp_cpy.node->left)
	{
		if (hp_cpy.node->args && hp_cpy.node->args->redir)
			red_res = redirect_and_exec(&hp_cpy);
		if (!red_res)
		{
			hp_cpy.node = hp_cpy.node->left;
			exit_code = execute_ast(&hp_cpy);
		}
		else
			exit_code = 1;
		clean_resources(&hp_cpy, saved_in, saved_out);
		exit(exit_code);
	}
	exit(0);
}

static void	subshell_handler(t_helper *hp, pid_t pid)
{
	t_env		*env_cpy;
	t_helper	hp_cpy;
	int			status;

	env_cpy = dup_env(*hp->env);
	hp_cpy.exit_status = hp->exit_status;
	hp_cpy.env = &env_cpy;
	hp_cpy.node = hp->node;
	if (pid == 0)
		subshell_worker(hp_cpy);
	else
	{
		waitpid(pid, &status, 0);
		hp->exit_status =  WEXITSTATUS(status);
	}
}

void	execute_herdocs(t_helper *hp)
{
	t_tree	*parent;

	if (!hp->node)
		return ;

	if ((hp->node->type == T_CMD || hp->node->type == T_SUBSHELL) && !hp->node->args->herdoc_file)
		get_last_heredoc(hp->node->args->redir, hp);

	if (hp->node->type == T_PIPE || hp->node->type == T_AND || hp->node->type == T_OR)
	{
		parent = hp->node;
		hp->node = parent->left;
		execute_herdocs(hp);
		hp->node = parent->right;
		execute_herdocs(hp);
		hp->node = parent;
	}
}

int	execute_ast(t_helper *hp)
{
	int			left_status;
	pid_t		pid;
	t_tree		*parent;

	setup_signals();

	if (!hp->node)
	{
		hp->exit_status = 1;
		return (hp->exit_status);
	}

	if (hp->node->args && hp->node->args->argv && hp->node->args->expand_list)
	{
		hp->node->args->argv_cpy = hp->node->args->argv;
		argv_expander(&hp->node->args->argv, hp->node->args->expand_list, *hp->env, hp->exit_status);
		if (contain_wildcard(hp->node->args->argv))
			expand_wildcard(&hp->node->args->argv);
	}

	if (hp->node->type == T_CMD)
		hp->exit_status = redirect_and_exec(hp);
	if (hp->node->type == T_PIPE)
		hp->exit_status = exec_pipe(hp);

	if (hp->node->type == T_AND)
	{
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

	if (hp->node->type == T_OR)
	{
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
