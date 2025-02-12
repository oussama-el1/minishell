/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:58:38 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/12 00:58:36 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int test_subshell_env(t_env *env)
{
    t_tree subshell_node;
    t_tree command_node;
    
    char *argv[] = {"export", "TEST_VAR=subshell_value", NULL};
    command_node.type = CMD;
    command_node.argv = argv;
    command_node.filename = NULL;
    command_node.heredoc_delim = NULL;
    command_node.is_subshell = 0;
    command_node.left = NULL;
    command_node.right = NULL;

    subshell_node.type = SUBSHELL;
    subshell_node.argv = NULL;
    subshell_node.filename = NULL;
    subshell_node.heredoc_delim = NULL;
    subshell_node.is_subshell = 1;
    subshell_node.left = &command_node;
    subshell_node.right = NULL;

    ft_putendl_fd("\n===== TEST: Subshell Variable Isolation (`(export TEST_VAR=subshell_value)`) =====", 1);
    execute_ast(&subshell_node, env);

    ft_putendl_fd("Checking if TEST_VAR exists in parent:", 1);
    if (get_env_var(env, "TEST_VAR"))
        ft_putendl_fd("❌ Failed: TEST_VAR modified in parent!", 2);
    else
        ft_putendl_fd("✅ Passed: TEST_VAR was isolated in subshell!", 1);
    
    return (0);
}

int test_subshell(t_env *env)
{
    t_tree subshell_node;
    t_tree and_node;
    t_tree cd_node;
    t_tree pipe_node;
    t_tree ls_node;
    t_tree grep_node;
    t_tree redir_node;

    char *cd_argv[] = {"cd", "/usr/bin", NULL};
    cd_node.type = CMD;
    cd_node.argv = cd_argv;
    cd_node.left = NULL;
    cd_node.right = NULL;

    char *ls_argv[] = {"ls", NULL};
    ls_node.type = CMD;
    ls_node.argv = ls_argv;
    ls_node.left = NULL;
    ls_node.right = NULL;

    char *grep_argv[] = {"grep", "gcc", NULL};
    grep_node.type = CMD;
    grep_node.argv = grep_argv;
    grep_node.left = NULL;
    grep_node.right = NULL;

    pipe_node.type = PIPE;
    pipe_node.left = &ls_node;
    pipe_node.right = &grep_node;

    and_node.type = AND;
    and_node.left = &cd_node;
    and_node.right = &pipe_node;

    subshell_node.type = SUBSHELL;
    subshell_node.left = &and_node;
    subshell_node.right = NULL;

    redir_node.type = REDIR_OUT;
    redir_node.filename = "output.txt";
    redir_node.left = &subshell_node;
    redir_node.right = NULL;

    ft_putendl_fd("\n===== TEST: Complex Subshell Execution (`(cd /usr/bin && ls | grep gcc) > output.txt`) =====", 1);
    execute_ast(&redir_node, env);

    ft_putendl_fd("Checking if `pwd` is still the same after subshell:", 1);
    execute_ast(&(t_tree){CMD, (char *[]){"pwd", NULL}, NULL, NULL, 0, NULL, NULL}, env);

    ft_putendl_fd("\n===== Checking contents of output.txt =====", 1);
    execute_ast(&(t_tree){CMD, (char *[]){"cat", "output.txt", NULL}, NULL, NULL, 0, NULL, NULL}, env);

    return (0);
}

/*

    (cd /usr/bin && ls | grep gcc) > output.txt

         REDIR_OUT
       (output.txt)
           │
        SUBSHELL
           │
       LOGICAL_AND
        /       \
     CMD        PIPE
   (cd /usr/bin) /   \
                CMD   CMD
               (ls)  (grep gcc)

*/

// int test_subshell(t_env *env)
// {
//     t_tree subshell_node;
//     t_tree command_node;

//     char *argv[] = {"echo", "Inside subshell", NULL};
//     command_node.type = CMD;
//     command_node.argv = argv;
//     command_node.filename = NULL;
//     command_node.heredoc_delim = NULL;
//     command_node.is_subshell = 0;
//     command_node.left = NULL;
//     command_node.right = NULL;

//     subshell_node.type = SUBSHELL;
//     subshell_node.argv = NULL;
//     subshell_node.filename = NULL;
//     subshell_node.heredoc_delim = NULL;
//     subshell_node.is_subshell = 1;
//     subshell_node.left = &command_node;
//     subshell_node.right = NULL;

//     ft_putendl_fd("\n===== TEST: Basic Subshell Execution (`(echo Inside subshell)`) =====", 1);
//     return execute_ast(&subshell_node, env);
// }
