/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:59:24 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/15 19:41:18 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int test(t_env *env, int *exit_status)
{
	// printf("\n==== TEST: Single Input Redirection `<` ====\n");
	// char *argv1[] = {"cat", NULL};
	// t_tree cmd1 = {CMD, argv1, NULL, 0, NULL, NULL};
	// t_redir in1 = {"input.txt", NULL, REDIR_IN, NULL};
	// cmd1.redirections = &in1;
	// execute_ast(&cmd1, env);

	// printf("\n==== TEST: Single Output Redirection `>` ====\n");
	// char *argv2[] = {"echo", "Hello, World!", NULL};
	// t_tree cmd2 = {CMD, argv2, NULL, 0, NULL, NULL};
	// t_redir out1 = {"output.txt", NULL, REDIR_OUT, NULL};
	// cmd2.redirections = &out1;
	// execute_ast(&cmd2, env);

	// printf("\n==== TEST: Single Append Redirection `>>` ====\n");
	// char *argv3[] = {"echo", "Appending...", NULL};
	// t_tree cmd3 = {CMD, argv3, NULL, 0, NULL, NULL};
	// t_redir out2 = {"append.txt", NULL, REDIR_APPEND, NULL};
	// cmd3.redirections = &out2;
	// execute_ast(&cmd3, env);

	// printf("\n==== TEST: Single Heredoc Redirection `<<` ====\n");
	// char *argv4[] = {"cat", NULL};
	// t_tree cmd4 = {CMD, argv4, NULL, 0, NULL, NULL};
	// t_redir heredoc1 = {NULL, "EOF", HEREDOC, NULL};
	// cmd4.redirections = &heredoc1;
	// execute_ast(&cmd4, env, exit_status);

	// printf("\n==== TEST: Input `<` and Output `>` ====\n");
	// char *argv5[] = {"cat", NULL};
	// t_tree cmd5 = {CMD, argv5, NULL, 0, NULL, NULL};
	// t_redir in2 = {"Makefile", NULL, REDIR_IN, NULL};
	// t_redir out3 = {"output.txt", NULL, REDIR_OUT, NULL};
	// in2.next = &out3;
	// cmd5.redirections = &in2;
	// execute_ast(&cmd5, env);

	// printf("\n==== TEST: Input `<` and Append `>>` ====\n");
	// char *argv6[] = {"cat", NULL};
	// t_tree cmd6 = {CMD, argv6, NULL, 0, NULL, NULL};
	// t_redir in3 = {"in.txt", NULL, REDIR_IN, NULL};
	// t_redir out4 = {"out.txt", NULL, REDIR_APPEND, NULL};
	// in3.next = &out4;
	// cmd6.redirections = &in3;
	// execute_ast(&cmd6, env);

	// printf("\n==== TEST: Input `<` and Heredoc `<<` ====\n");
	// char *argv7[] = {"cat", NULL};
	// t_tree cmd7 = {CMD, argv7, NULL, 0, NULL, NULL};
	// t_redir heredoc2 = {"in.txt", NULL, REDIR_IN, NULL};
	// t_redir in4 = {NULL, "EOF", HEREDOC, NULL};
	// in4.next = &heredoc2;
	// cmd7.redirections = &in4;
	// execute_ast(&cmd7, env, exit_status);

	// printf("\n==== TEST: Output `>` and Append `>>` ====\n");
	// char *argv8[] = {"echo", "Chaining Output", NULL};
	// t_tree cmd8 = {CMD, argv8, NULL, 0, NULL, NULL};
	// t_redir out5 = {"file1.txt", NULL, REDIR_OUT, NULL};
	// t_redir out6 = {"file2.txt", NULL, REDIR_APPEND, NULL};
	// out5.next = &out6;
	// cmd8.redirections = &out5;
	// execute_ast(&cmd8, env);

	// printf("\n==== TEST: Input `<` and Output `>` and Append `>>` ====\n");
	// char *argv9[] = {"ls", "-l", NULL};
	// t_tree cmd9 = {CMD, argv9, NULL, 0, NULL, NULL};
	// t_redir in5 = {"input.txt", NULL, REDIR_IN, NULL};
	// t_redir out7 = {"output.txt", NULL, REDIR_OUT, NULL};
	// t_redir out8 = {"append.txt", NULL, REDIR_APPEND, NULL};
	// in5.next = &out7;
	// out7.next = &out8;
	// cmd9.redirections = &in5;
	// execute_ast(&cmd9, env);

    printf("\n==== TEST: Input `<` and Heredoc `<<` and Output `>` ====\n");
    char *argv10[] = {"hhhhh", NULL};
    t_tree cmd10 = {CMD, argv10, NULL, 0, NULL, NULL};
    t_redir in6 = {"Makefile", NULL, REDIR_IN, NULL};
    t_redir heredoc3 = {NULL, "EOF", HEREDOC, NULL};
    t_redir out9 = {"output.txt", NULL, REDIR_OUT, NULL};
    in6.next = &heredoc3;
    heredoc3.next = &out9;
    cmd10.redirections = &in6;
    execute_ast(&cmd10, env, exit_status);

	return (0);
}

/*
	(CMD : cat) - > redirections : in (input.txt)-> out (output.txt)
*/
