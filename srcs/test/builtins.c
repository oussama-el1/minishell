// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   builtins.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/04 00:46:10 by oel-hadr          #+#    #+#             */
// /*   Updated: 2025/02/12 16:25:03 by oel-hadr         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/minishell.h"

// void test_export(t_env *env)
// {
// 	printf("\n=== Testing export ===\n");

// 	// ✅ Case 1: Assign a new variable
// 	// char *case1[] = {"export", "MYVAR=hello", NULL};
// 	// t_tree cmd1 = {CMD, case1, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd1, env);

// 	// char *case99[] = {"export", NULL};
// 	// t_tree cmd99 = {CMD, case99, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd99, env);
	
// 	// // ✅ Case 2: Append value using +=
// 	// char *case2[] = {"export", "MYVAR+=world", NULL};
// 	// t_tree cmd2 = {CMD, case2, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd2, env);

// 	// char *case999[] = {"export", NULL};
// 	// t_tree cmd999 = {CMD, case999, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd999, env);

// 	// // ✅ Case 3: Declare a variable without a value
// 	// char *case3[] = {"export", "NEWVAR", NULL};
// 	// t_tree cmd3 = {CMD, case3, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd3, env);

// 	// // ✅ Case 4: Assign an empty value
// 	// char *case4[] = {"export", "NEWVAR=", NULL};
// 	// t_tree cmd4 = {CMD, case4, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd4, env);

// 	// char *case999[] = {"export", NULL};
// 	// t_tree cmd999 = {CMD, case999, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd999, env);

// 	// // ✅ Case 5: Invalid variable name (should print an error)
// 	// char *case5[] = {"export", "123INVALID=val", NULL};
// 	// t_tree cmd5 = {CMD, case5, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd5, env);

// 	// // ✅ Case 6: Valid underscore variable
// 	// char *case6[] = {"export", "_UNDERSCORE=allowed", NULL};
// 	// t_tree cmd6 = {CMD, case6, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd6, env);

// 	// // ✅ Case 7: Invalid concatenation (missing `=`)
// 	// char *case7[] = {"export", "VAR+wrong", NULL};
// 	// t_tree cmd7 = {CMD, case7, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd7, env);

// 	// ✅ Case 8: Appending to PATH
// 	// char *case8[] = {"export", "PATH+=:/usr/sbin", NULL};
// 	// t_tree cmd8 = {CMD, case8, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd8, env);

// 	// // ✅ Case 9: Assign and append in one command
// 	// char *case9[] = {"export", "VAR=hello", "VAR+=world", NULL};
// 	// t_tree cmd9 = {CMD, case9, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd9, env);

// 	// ✅ Case 10: Append with space
// 	char *case10[] = {"export", "VAR+= world", NULL};
// 	t_tree cmd10 = {CMD, case10, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd10, env);

// 	// // ✅ Case 11: Print all exported variables
// 	// char *case11[] = {"export", NULL};
// 	// t_tree cmd11 = {CMD, case11, NULL, NULL, 0, NULL, NULL};
// 	// exec_command(&cmd11, env);

// 	printf("\n=== Done Testing export ===\n");
// }

// void	test_unset(t_env *env)
// {
// 	printf("=== Testing unset ===\n");

// 	char *case1[] = {"export", "TESTVAR=hello", NULL};
// 	t_tree cmd1 = {CMD, case1, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd1, env);

// 	// Should remove TESTVAR
// 	char *case2[] = {"unset", "TESTVAR", NULL};
// 	t_tree cmd2 = {CMD, case2, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd2, env);

//  	// Should return an error
// 	char *case3[] = {"unset", "123VAR", NULL};
// 	t_tree cmd3 = {CMD, case3, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd3, env);
// }

// void	test_exit(t_env *env)
// {
// 	printf("=== Testing exit ===\n");

// 	char *case1[] = {"exit", NULL};
// 	t_tree cmd1 = {CMD, case1, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd1, env); // Should exit with status 0

// 	char *case2[] = {"exit", "42", NULL};
// 	t_tree cmd2 = {CMD, case2, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd2, env); // Should exit with status 42

// 	char *case3[] = {"exit", "abc", NULL};
// 	t_tree cmd3 = {CMD, case3, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd3, env); // Should print error and exit 255

// 	char *case4[] = {"exit", "1", "2", NULL};
// 	t_tree cmd4 = {CMD, case4, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd4, env); // Should print error but NOT exit
// }

// void	test_env(t_env *env)
// {
// 	printf("=== Testing env ===\n");

// 	char *case1[] = {"env", NULL};
// 	t_tree cmd1 = {CMD, case1, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd1, env); // Should list all exported variables

// 	char *case2[] = {"env", "hh", NULL};
// 	t_tree cmd2 = {CMD, case2, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd2, env);
// }

// void	test_cd(t_env *env)
// {
//     printf("=== Testing cd ===\n");

//     char *case1[] = {"cd", NULL};
//     t_tree cmd1 = {CMD, case1, NULL, NULL, 0, NULL, NULL};
//     exec_command(&cmd1, env); // Should go to $HOME
// 	ft_printf("OLDPWD: %s\n", get_env_var(env, "OLDPWD"));
// 	ft_printf("pwd: %s\n", get_env_var(env, "PWD"));

//     char *case2[] = {"cd", "/usr", NULL};
//     t_tree cmd2 = {CMD, case2, NULL, NULL, 0, NULL, NULL};
//     exec_command(&cmd2, env); // Should change to /usr
// 	ft_printf("OLDPWD: %s\n", get_env_var(env, "OLDPWD"));
// 		ft_printf("pwd: %s\n", get_env_var(env, "PWD"));

//     char *case3[] = {"cd", "unknown_dir", NULL};
//     t_tree cmd3 = {CMD, case3, NULL, NULL, 0, NULL, NULL};
//     exec_command(&cmd3, env); // Should print error
// 	ft_printf("OLDPWD: %s\n", get_env_var(env, "OLDPWD"));
// 	ft_printf("pwd: %s\n", get_env_var(env, "PWD"));
// }

// void test_echo(t_env *env)
// {
// 	printf("=== Testing echo ===\n");

// 	char *case1[] = {"echo", "hello", "world", NULL};
// 	t_tree cmd1 = {CMD, case1, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd1, env);

// 	char *case2[] = {"echo", "-n", "hello", "world", NULL};
// 	t_tree cmd2 = {CMD, case2, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd2, env);
// 	printf(" <-- No newline expected\n");

// 	char *case3[] = {"echo", "-n", "-n", "hello", NULL};
// 	t_tree cmd3 = {CMD, case3, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd3, env);
// 	printf(" <-- No newline expected\n");

// 	char *case4[] = {"echo", "-nnnn", "hello", NULL};
// 	t_tree cmd4 = {CMD, case4, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd4, env);
// 	printf(" <-- No newline expected\n");

// 	char *case5[] = {"echo", "", NULL};
// 	t_tree cmd5 = {CMD, case5, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd5, env);

// 	char *case6[] = {"echo", "\"hello world\"", NULL};
// 	t_tree cmd6 = {CMD, case6, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd6, env);

// 	char *case7[] = {"echo", "'hello world'", NULL};
// 	t_tree cmd7 = {CMD, case7, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd7, env);

// 	char *case8[] = {"echo", "$HOME", NULL};
// 	t_tree cmd8 = {CMD, case8, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd8, env);

// 	char *case9[] = {"echo", "'$HOME'", NULL};
// 	t_tree cmd9 = {CMD, case9, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd9, env);

// 	char *case10[] = {"echo", "hello$USER", NULL};
// 	t_tree cmd10 = {CMD, case10, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd10, env);

// 	char *case11[] = {"echo", "hello", "$USER", NULL};
// 	t_tree cmd11 = {CMD, case11, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd11, env);

// 	char *case12[] = {"echo", "hello", "$USER!", NULL};
// 	t_tree cmd12 = {CMD, case12, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd12, env);

// 	char *case13[] = {"echo", "hello", "\"world\"", NULL};
// 	t_tree cmd13 = {CMD, case13, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd13, env);

// 	char *case14[] = {"echo", "-n", "-n", "-n", "test", NULL};
// 	t_tree cmd14 = {CMD, case14, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd14, env);
// 	printf(" <-- No newline expected\n");

// 	char *case15[] = {"echo", "-nnnn", "test", NULL};
// 	t_tree cmd15 = {CMD, case15, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd15, env);
// 	printf(" <-- No newline expected\n");

// 	printf("=== Done Testing echo ===\n");
// }

// void	test_pwd(t_env *env)
// {
// 	printf("=== Testing pwd ===\n");

// 	char *case1[] = {"pwd", NULL};
// 	t_tree cmd1 = {CMD, case1, NULL, NULL, 0, NULL, NULL};
// 	exec_command(&cmd1, env); // Should print current directory
// }
