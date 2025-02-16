// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   and.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/08 20:50:18 by oel-hadr          #+#    #+#             */
// /*   Updated: 2025/02/08 21:31:56 by oel-hadr         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/minishell.h"

// int test_and_operator(t_env *env)
// {
// 	t_tree parent;
// 	t_tree left;
// 	t_tree right;

// 	parent.type = AND;
// 	parent.argv = NULL;
// 	parent.filename = NULL;
// 	parent.heredoc_delim = NULL;
// 	parent.is_subshell = 0;
// 	parent.left = &left;
// 	parent.right = &right;

// 	char *argv1[] = {"echo", "command 1", NULL};
// 	left.type = CMD;
// 	left.argv = argv1;
// 	left.filename = NULL;
// 	left.heredoc_delim = NULL;
// 	left.is_subshell = 0;
// 	left.left = NULL;
// 	left.right = NULL;

// 	char *argv2[] = {"echo", "command 2", NULL};
// 	right.type = CMD;
// 	right.argv = argv2;
// 	right.filename = NULL;
// 	right.heredoc_delim = NULL;
// 	right.is_subshell = 0;
// 	right.left = NULL;
// 	right.right = NULL;
	
// 	return (execute_ast(&parent, env));
// }

// /*

// ls -l && cat MaKefile 

// */