/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:01:22 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/13 14:40:43 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void test_simple_command(t_env *env)
// {
// 	char *arg1[] = {"pwd", NULL};
// 	t_tree cmd1 = {CMD, arg1, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd1, env);

// 	char *arg2[] = {"cd", NULL};
// 	t_tree cmd2 = {CMD, arg2, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd2, env);

// 	char *arg3[] = {"pwd", NULL};
// 	t_tree cmd3 = {CMD, arg3, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd3, env);
// }

// void test_absolute_cmd(t_env *env)
// {
// 	char *arg1[] = {"/usr/ls", NULL};
// 	t_cmd cmd1 = {arg1, NULL, NULL, 0, env, NULL};
// 	exec_command(&cmd1);

// 	char *arg2[] = {"/usr/bin/grep", NULL};
// 	t_cmd cmd2 = {arg2, NULL, NULL, 0, env, NULL};
// 	exec_command(&cmd2);

// 	char *arg3[] = {"/find", NULL};
// 	t_cmd cmd3 = {arg3, NULL, NULL, 0, env, NULL};
// 	exec_command(&cmd3);

// 	char *arg4[] = {"/usr/mv", NULL};
// 	t_cmd cmd4 = {arg4, NULL, NULL, 0, env, NULL};
// 	exec_command(&cmd4);
// }

// void test_relative_cmd(t_env *env)
// {
// 	char *arg1[] = {"../ls", NULL};
// 	t_cmd cmd1 = {arg1, NULL, NULL, 0, env, NULL};
// 	exec_command(&cmd1);

// 	char *arg2[] = {"./bin/grep", NULL};
// 	t_cmd cmd2 = {arg2, NULL, NULL, 0, env, NULL};
// 	exec_command(&cmd2);

// 	char *arg3[] = {"../hh/find", NULL};
// 	t_cmd cmd3 = {arg3, NULL, NULL, 0, env, NULL};
// 	exec_command(&cmd3);

// 	char *arg4[] = {"./mv", NULL};
// 	t_cmd cmd4 = {arg4, NULL, NULL, 0, env, NULL};
// 	exec_command(&cmd4);
// }
