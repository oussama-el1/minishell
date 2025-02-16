/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 09:28:11 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/15 13:41:08 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	test_pipes(t_env *env)
{
	(void)env;	
// 	int result;

	// ft_putendl_fd("\n===== TEST: Simple Pipe (`echo hello | cat`) =====", 1);
	// t_tree pipe1;
	// t_tree cmd1, cmd2;
	// char *argv1[] = {"echo", "hello", NULL};
	// char *argv2[] = {"wc", "-l", NULL};

	// cmd1 = (t_tree){CMD, argv1, NULL, 0, NULL, NULL};
	// cmd2 = (t_tree){CMD, argv2, NULL, 0, NULL, NULL};
	// pipe1 = (t_tree){PIPE, NULL, NULL, 0, &cmd1, &cmd2};

	// result = execute_ast(&pipe1, env);
	// if (result == 0)
	// 	ft_putendl_fd("✅ Passed", 1);
	// else
	// 	ft_putendl_fd("❌ Failed", 2);

	/*
	
	
	*/

	/* ----------------------------------------------- */

	// ft_putendl_fd("\n===== TEST: Multiple Pipes (`echo hello | grep h | wc -c`) =====", 1);
	// t_tree pipe2, cmd3;
	// char *argv3[] = {"grep", "h", NULL};
	// char *argv4[] = {"wc", "-c", NULL};

	// cmd3 = (t_tree){CMD, argv3, NULL, 0, NULL, NULL};
	// t_tree cmd4 = {CMD, argv4, NULL, 0, NULL, NULL};
	// pipe2 = (t_tree){PIPE, NULL, NULL, 0, &cmd3, &cmd4};
	// pipe1.right = &pipe2; // Linking the first pipe to the second

	// result = execute_ast(&pipe1, env);
	// if (result == 0)
	//     ft_putendl_fd("✅ Passed", 1);
	// else
	//     ft_putendl_fd("❌ Failed", 2);

	/*
			(PIPE)
			/    \
		(CMD)    (PIPE)
		"echo"    /    \
				(CMD)   (CMD)
				"grep"    "wc"
	*/

	// /* ----------------------------------------------- */

	// ft_putendl_fd("\n===== TEST: Pipe with Redirection (`ls | grep .c > result.txt`) =====", 1);
	// char *argv5[] = {"ls", NULL};
	// char *argv6[] = {"grep", ".c", NULL};

	// cmd1 = (t_tree){CMD, argv5, NULL, 0, NULL, NULL};
	// cmd2 = (t_tree){CMD, argv6, NULL, 0, NULL, NULL};
	// pipe1 = (t_tree){PIPE, NULL, NULL, 0, &cmd1, &cmd2};
	// t_redir out_redir = {"result.txt", NULL, REDIR_OUT, NULL};

	// cmd2.redirections = &out_redir;

	// result = execute_ast(&pipe1, env);
	// if (result == 0 && access("result.txt", F_OK) == 0)
	//     ft_putendl_fd("✅ Passed", 1);
	// else
	//     ft_putendl_fd("❌ Failed", 2);

	/*
		 PIPE
		/	 \
	   ls 	 grep .c -> redirections : [result.txt (REDIR_OUT), NULL]
	*/

	// /* ----------------------------------------------- */

	// ft_putendl_fd("\n===== TEST: Logical AND (`echo Hello && echo World`) =====", 1);
	// t_tree and1;
	// char *argv7[] = {"echo", "Hello", NULL};
	// char *argv8[] = {"echo", "World", NULL};

	// cmd1 = (t_tree){CMD, argv7, NULL, 0, NULL, NULL};
	// cmd2 = (t_tree){CMD, argv8, NULL, 0,NULL, NULL};
	// and1 = (t_tree){AND, NULL, NULL, 0, &cmd1, &cmd2};

	// result = execute_ast(&and1, env);
	// if (result == 0)
	//     ft_putendl_fd("✅ Passed", 1);
	// else
	//     ft_putendl_fd("❌ Failed", 2);

	// /* ----------------------------------------------- */

	// ft_putendl_fd("\n===== TEST: Logical OR (`false || echo Hello`) =====", 1);
	// t_tree or1;
	// char *argv9[] = {"false", NULL};
	// char *argv10[] = {"echo", "Hello", NULL};

	// cmd1 = (t_tree){CMD, argv9, NULL, 0,NULL, NULL};
	// cmd2 = (t_tree){CMD, argv10, NULL, 0, NULL, NULL};
	// or1 = (t_tree){OR, NULL, NULL, 0, &cmd1, &cmd2};

	// result = execute_ast(&or1, env);
	// if (result == 0)
	//     ft_putendl_fd("✅ Passed", 1);
	// else
	//     ft_putendl_fd("❌ Failed", 2);

	// /* ----------------------------------------------- */

	// ft_putendl_fd("\n===== TEST: Subshell (`(echo Hello; ls)`) =====", 1);
	// t_tree subshell1;
	// char *argv11[] = {"ls", NULL};

	// cmd1 = (t_tree){CMD, argv7, NULL, 0, NULL, NULL};
	// cmd2 = (t_tree){CMD, argv11, NULL, 0, NULL, NULL};
	// and1 = (t_tree){AND, NULL, NULL, 0, &cmd1, &cmd2};
	// subshell1 = (t_tree){SUBSHELL, NULL, NULL, 1, &and1, NULL};

	// result = execute_ast(&subshell1, env);
	// if (result == 0)
	//     ft_putendl_fd("✅ Passed", 1);
	// else
	//     ft_putendl_fd("❌ Failed", 2);

	// /* ----------------------------------------------- */

	// ft_putendl_fd("\n===== TEST: Combination (`cat < input.txt | grep test | sort > output.txt`) =====", 1);
	// t_tree pipe3, pipe4;
	// char *argv12[] = {"cat", NULL};
	// char *argv13[] = {"grep", "test", NULL};
	// char *argv14[] = {"sort", NULL};

	// t_redir input_redir = {"input.txt", NULL, REDIR_IN, NULL};
	// t_redir output_redir = {"output.txt", NULL, REDIR_OUT, NULL};

	// cmd1 = (t_tree){CMD, argv12, &input_redir, 0, NULL, NULL};
	// cmd2 = (t_tree){CMD, argv13, NULL, 0, NULL, NULL};
	// t_tree cmd3_sort = {CMD, argv14, &output_redir, 0, NULL, NULL};

	// pipe4 = (t_tree){PIPE, NULL, NULL, 0, &cmd2, &cmd3_sort};
	// pipe3 = (t_tree){PIPE, NULL, NULL, 0, &cmd1, &pipe4};

	// result = execute_ast(&pipe3, env);
	// if (result == 0 && access("output.txt", F_OK) == 0)
	//     ft_putendl_fd("✅ Passed", 1);
	// else
	//     ft_putendl_fd("❌ Failed", 2);

	/*
		    (PIPE)
			/    \
		(CMD)    (PIPE)
		"cat"    /    \
				(CMD)   (CMD)
				"grep"    "sort"			
	*/

	return 0;
}


