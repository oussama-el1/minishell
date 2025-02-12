/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 23:25:06 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/09 00:13:16 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int test_pipe(t_env *env)
{
	t_tree parent;  // Root node (PIPE)
	t_tree middle;  // Middle PIPE node
	t_tree left;    // First command node (ls -l)
	t_tree right;   // Last command node (wc -l)
	t_tree mid_cmd; // Middle command node (grep Makefile)

	// ✅ Root node (PIPE between `grep Makefile` and `wc -l`)
	parent.type = PIPE;
	parent.argv = NULL;
	parent.filename = NULL;
	parent.heredoc_delim = NULL;
	parent.is_subshell = 0;
	parent.left = &middle;
	parent.right = &right;

	// ✅ Middle PIPE node (PIPE between `ls -l` and `grep Makefile`)
	middle.type = PIPE;
	middle.argv = NULL;
	middle.filename = NULL;
	middle.heredoc_delim = NULL;
	middle.is_subshell = 0;
	middle.left = &left;
	middle.right = &mid_cmd;

	// ✅ First command node (`ls -l`)
	char *argv1[] = {"ls", "-l", NULL};
	left.type = CMD;
	left.argv = argv1;
	left.filename = NULL;
	left.heredoc_delim = NULL;
	left.is_subshell = 0;
	left.left = NULL;
	left.right = NULL;

	// ✅ Middle command node (`grep Makefile`)
	char *argv2[] = {"grep", "Makefile", NULL};
	mid_cmd.type = CMD;
	mid_cmd.argv = argv2;
	mid_cmd.filename = NULL;
	mid_cmd.heredoc_delim = NULL;
	mid_cmd.is_subshell = 0;
	mid_cmd.left = NULL;
	mid_cmd.right = NULL;

	// ✅ Last command node (`wc -l`)
	char *argv3[] = {"wc", "-l", NULL};
	right.type = CMD;
	right.argv = argv3;
	right.filename = NULL;
	right.heredoc_delim = NULL;
	right.is_subshell = 0;
	right.left = NULL;
	right.right = NULL;

	// ✅ Execute the pipeline
	return (execute_ast(&parent, env));
}


/*

        PIPE
       /    \
   PIPE      wc -l
  /    \
ls -l   grep Makefile

  
*/