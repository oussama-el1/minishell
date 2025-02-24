/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:11:42 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/24 15:05:51 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>

int g_received_signal;

typedef enum e_tree_type
{
	AND,
	OR,
	PIPE,
	CMD,
	SUBSHELL
} t_tree_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR_APPEND,
} t_redir_type;


typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	char			*filename;
	char			*heredoc_delim;
	t_redir_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_tree
{
	t_tree_type		type;
	char			**argv;
	t_redir			*redirections;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;


typedef struct s_expand {
	bool	expanded;
	int		start;
	int		end;
} t_expand;

// builtins
int	ft_cd(char **argv, t_env *env, int exit_status);
int	ft_echo(char **argv);
int	exec_command(t_tree *cmd, t_env *env, int exit_status);
int	ft_pwd(t_env *env, int exit_status);
int	ft_export(char **argv, t_env *env, int exit_status);
int	ft_unset(char **argv, t_env *env);
int	ft_env(char **argv, t_env *env);
int	ft_exit(char **argv);
int	not_valid_idenrifier(char *env, char *name, char *value);


// helpers
int		validate_var_name(const char *var);
int		set_name_and_value(char *env, char **name,
		char **value);

// tests
// void	test_export(t_env *env);
// void	test_unset(t_env *env);
// void	test_exit(t_env *env);
// void	test_env(t_env *env);
// void	test_cd(t_env *env);
// void	test_echo(t_env *env);
// void	test_pwd(t_env *env);
// void	test_simple_command(t_env *env);
// int		test_redirection_in(t_env *env);
// int		test_redirection_out(t_env *env);
// int		test_herdoc(t_env *env);
// int		test_and_operator(t_env *env);
// int		test_or_operator(t_env *env);
// int		test_pipe(t_env *env);
// int		test_pipes(t_env *env);
// int		test_subshell_env(t_env *env);
// int		test_subshell(t_env *env);
// int		test_shell_restore(t_env *env);
// int		test(t_env *env, int *exit_status);

// env_utils
t_env	*init_env(char **envp);
void	add_env_var(t_env **env, char *key,
		char *value, int exported);
void	print_export(t_env *env, int declare);
void	print_env(t_env *env);
int		unset_env_var(t_env **env, char *key);
char	*get_env_var(t_env *env, char *key, int exit_status);
void	set_env_var(t_env **env, char *key, char *value, int exported);
void	free_env(t_env *env);
char	**get_env_array(t_env *env);
t_env	*dup_env(t_env *original);

// exec
char	*get_executable_path(char *cmd, t_env *env, int exit_status);
int		execute_ast(t_tree *node, t_env *env, int *exit_status);
int		exec_binary(char **argv, t_env *env, int exit_status);
int		exec_cmd(t_tree *node, t_env *env, int exit_status);
int		exec_pipe(t_tree *node, t_env *env, int *exec_pipe);

void	setup_signals(void);
void	rl_replace_line(const char *text, int clear_undo);

void	expand_env_herdoc(t_env *env, char *line, int fd, int exit_status);
void	herdoc_loop(const char *delimiter, t_env *env, int fd, int exit_status);
void	handle_heredoc(const char *delimiter, t_env *env, int exit_status);
int		get_last_heredoc(t_redir *redirection, t_redir **last_heredoc, int exit_status, t_env *env);
void	file_error_handler(t_redir *redirection, int *error_found);
void	clean_resources(int saved_in, int saved_out);
void	argv_expander(char **argv, t_expand *expandArr, t_env *env, int exit_status);


# endif
