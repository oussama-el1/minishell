// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   redirection.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/07 16:42:49 by oel-hadr          #+#    #+#             */
// /*   Updated: 2025/02/08 21:44:02 by oel-hadr         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/minishell.h"

// int test_redirection_out(t_env *env)
// {
// 	t_tree  node;
// 	t_tree  node_left;
// 	int     result;

// 	(void)env;
// 	ft_putendl_fd("\n===== TEST: Output Redirection (`>`) with valid file =====", 1);
	
// 	node_left.type = CMD;
// 	char *argv[] = {"echo", "-n", "hello world", NULL};
// 	node_left.argv = argv;
// 	node_left.filename = NULL;
// 	node_left.left = NULL;
// 	node_left.right = NULL;

// 	node.type = REDIR_APPEND;
// 	node.filename = "output.txt";
// 	node.left = &node_left;
// 	node.right = NULL;

// 	result = execute_ast(&node, env);

// 	if (result == 0 && access("output.txt", F_OK) == 0)
// 		ft_putendl_fd("✅ Passed", 1);
// 	else
// 		ft_putendl_fd("❌ Failed", 2);

// 	return (0);
// }

// int test_redirection_in(t_env *env)
// {
// 	t_tree  node;
// 	t_tree  node_left;
// 	int     result;

// 	(void)env;
// 	ft_putendl_fd("\n===== TEST: Output Redirection (`>`) with valid file =====", 1);
	
// 	node_left.type = CMD;
// 	char *argv[] = {"cat", "-e", };
// 	node_left.argv = argv;
// 	node_left.filename = NULL;
// 	node_left.left = NULL;
// 	node_left.right = NULL;

// 	node.type = REDIR_IN;
// 	node.filename = "output.txt";
// 	node.left = &node_left;
// 	node.right = NULL;

// 	result = execute_ast(&node, env);

// 	if (result == 0)
// 		ft_putendl_fd("✅ Passed", 1);
// 	else
// 		ft_putendl_fd("❌ Failed", 2);

// 	return (0);
// }

// int test_herdoc(t_env *env)
// {
// 	t_tree  node;
// 	t_tree  node_left;
// 	int     result;

// 	(void)env;
// 	ft_putendl_fd("\n===== TEST: HERDOC  (`<<`) with valid case =====", 1);
	
// 	node_left.type = CMD;
// 	char *argv[] = {"cat", NULL};
// 	node_left.argv = argv;
// 	node_left.filename = NULL;
// 	node_left.left = NULL;
// 	node_left.right = NULL;
// 	node_left.heredoc_delim = NULL;

// 	node.type = HEREDOC;
// 	node.heredoc_delim = "EOF";
// 	node.left = &node_left;
// 	node.right = NULL;

// 	result = execute_ast(&node, env);

// 	if (result == 0)
// 		ft_putendl_fd("✅ Passed", 1);
// 	else
// 		ft_putendl_fd("❌ Failed", 2);

// 	return (0);
// }
