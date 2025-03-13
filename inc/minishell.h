/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:11:42 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/13 20:54:18 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>

extern int	g_exit_status;

enum e_token_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	PIPE,
	AND,
	OR,
	DOLLAR,
	OPEN_BRACKET,
	CLOSED_BRACKET,
	D_Q,
	S_Q,
	EXPR,
} ;

typedef enum e_tree_type
{
	T_AND,
	T_OR,
	T_PIPE,
	T_CMD,
	T_SUBSHELL
}	t_tree_type;

typedef enum e_redir_type
{
	R_REDIR_IN,
	R_REDIR_OUT,
	R_REDIR_APPEND,
	R_HEREDOC,
}	t_redir_type;

enum e_gc
{
	ALLOC,
	FREE,
	FULLFREE,
	CMD,
	ENV,
	OPEN,
	CLEAR,
} ;

typedef struct s_token
{
	char			*value;
	int				type;
	int				visited;
	int				bef_space;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_expand
{
	bool			expanded;
	int				type;
	size_t			start;
	size_t			end;
	struct s_expand	*next;
	struct s_expand	*prev;
}	t_expand;

typedef struct s_redir
{
	char			*filename;
	char			*h_del;
	t_expand		*expand_list;
	t_redir_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_args
{
	char		**argv;
	char		**argv_cpy;
	t_expand	**expand_list;
	t_redir		*redir;
	bool		*wildcards;
	char		*herdoc_file;
	int			herdoc_idx;
	int			expnaded;
}	t_args;

typedef struct s_tree
{
	t_tree_type		type;
	t_args			*args;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

typedef struct s_helper
{
	int			line_count;
	int			splited;
	int			export;
	t_env		**env;
	t_tree		*node;
}	t_helper;

typedef struct s_hredir
{
	t_redir	*last_in;
	t_redir	*last_out;
	t_redir	*last_heredoc;
	int		last_her_idx;
	int		last_in_idx;
}	t_hredir;

typedef struct s_vars
{
	char			*cmd;
	int				flag;
	int				tmp;
	int				i;
}				t_vars;

typedef struct s_token_map
{
	const char			*key;
	enum e_token_type	type;
}	t_token_map;

typedef struct s_syntax
{
	int		inside_brackets;
	int		bracket_level;
	t_token	*start;
	t_token	*next_after;
}	t_syntax;

typedef struct s_ambiguous_err
{
	char	*filename;
	int		index;
}	t_ambiguous_err;

// Garbage Collector
typedef struct s_gc
{
	void		*mallocedptr;
	int			type;
	struct s_gc	*next;
	struct s_gc	*prev;
}	t_gc;

typedef struct s_fd_gc
{
	int					fd;
	char				*filename;
	int					type;
	struct s_fd_gc		*next;
}	t_fd_gc;

typedef struct s_gc_manager
{
	t_gc		*gc;
	int			first_iter;
}	t_gc_manager;

/* helper.c && helper2.c && string_utils.c && list_utils.c */
int			is_space(char c);
int			empty(char *str);
int			isquote(char c);
int			special_d(char c);
int			isparenth(char c);
int			is_alnum(char c);
int			isredirect(enum e_token_type type);
int			is_dilim(enum e_token_type type);
int			non_control(enum e_token_type type);
int			islogical(enum e_token_type type);
int			is_quote(enum e_token_type type);
int			is_regular(enum e_token_type type);
int			get_type(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
t_token		*last_token(t_token *token);
t_token		*lst_dup(t_token *token);
t_token		*sublist(t_token *start, t_token *end);
int			contains_unquoted_ampersand(const char *str);
char		*remove_quote(t_token *curr, char *str);
void		is_wildcard(t_token *curr, bool *wildcard);
int			non_control2(enum e_token_type type);
char		*input_cmd(t_token *token);
void		concat_str(char **arg, char *tmp, int bef_space);

/* syntax_helper.c */
int			print_syntax_error(char *token);
int			check_brackets(t_token *token);
void		while_ft(t_token **token, t_token **last, t_syntax *syntax);
int			check_operators(t_token *token);
int			check_redirections(t_token *token);
void		herdoc_msg(const char *delimiter, t_helper *hp);
int			end_with_op(t_token *token);
void		init_token(t_token **token, int allocate);
int			before_space(char *str, int i);
int			process_input(char *line, t_token **token,
				t_helper *helper, int base);
void		init_vars(t_vars **vars, char *line);
void		ft_newnode(t_token **token, char *value, int before_space);
char		*get_next_line(int fd);

// /* parsing_type.c && parser.c */
void		ft_space(t_vars **vars, int *ret);
void		parse_char(t_token **token, t_vars **vars, int *ret);
int			parse_quote(t_token **token, t_vars **vars, int *ret);
void		parse_dollar(t_token **token, t_vars **vars, int *ret);
void		parse_separator(t_token **token, t_vars **vars, int *ret);
void		parse_parenthesis(t_token **token, t_vars **vars, int *ret);
int			check_syntax(t_token *token);
void		init_setup(t_helper *hp, t_env **env);

/* tree.c */
t_tree		*build_ast(t_token *token);
t_tree		*fetch_pipe_or_subshell(t_token *token);
t_tree		*found_logical(t_token *token);
t_tree		*found_pipe(t_token *token, int subshell);
t_tree		*create_node(t_token *token);
void		skip_brackets_next(t_token **token, int *has_brackets);
void		skip_brackets_prev(t_token **token);
t_tree		*create_subshell(t_token *token);
t_tree		*create_cmd(t_token *token);
void		extract_args(t_args *args, t_token *token);
t_tree_type	get_tree_type(int type);
t_token		*back_prev(t_token *token);
char		*quoted_process(t_token **curr,
				t_expand **expansion_list, bool *wildcard);
t_token		*left_back(t_token *token);
int			args_count(t_token *token);
void		expansion_func(t_expand	**head, t_token *curr,
				char **str, size_t *start);
void		handle_redirection(t_redir **redir_list, t_token **curr);
void		extract_subshell_args(t_args **args, t_token *token);
void		process_token(t_token **curr, t_args *args,
				t_redir **redir, int *i);

// builtins
int			ft_cd(char **argv, t_env *env);
int			ft_echo(char **argv, char **arg_cpy);
int			exec_command(t_tree *cmd, t_helper *hp);
int			ft_pwd(t_env *env);
int			ft_export(char **argv, t_helper *hp);
int			ft_unset(char **argv, t_env **env);
int			ft_env(char **argv, t_env *env);
int			ft_exit(char **argv1);
int			not_valid_idenrifier(char *env);

// env_utils
t_env		*init_env(char **envp);
void		add_env_var(t_env **env, char *key,
				char *value, int exported);
void		print_export(t_env *env, int declare);
void		print_env(t_env *env);
int			unset_env_var(t_env **env, char *key);
char		*get_env_var(t_env *env, char *key);
void		set_env_var(t_env **env, char *key, char *value, int exported);
char		**get_env_array(t_env *env);
t_env		*dup_env(t_env *original);
int			validate_var_name(const char *var);
int			set_name_and_value(char *env, char **name, char **value);

// exec
void		setup_signals(void);
char		*get_executable_path(char *cmd, t_env *env);
void		execute_herdocs(t_helper *hp);
void		execute_ast(t_helper *hp);
int			exec_binary(char **argv, t_env *env);
void		redirect_and_exec(t_helper *hp);
void		exec_pipe(t_helper *hp);
void		rl_replace_line(const char *text, int clear_undo);
void		herdoc_loop(const char *delimiter, int fd, t_helper *hp);
char		*handle_heredoc(const char *delimiter, t_helper *hp, int mode);
void		herdoc_runner(t_redir *redirection, t_helper *hp);
void		file_error_handler(t_redir *redirection, int *error_found,
				int ambigous, t_ambiguous_err *err);
void		clean_resources(t_helper *hp, int saved_in, int saved_out);
char		**expand_one_arg(char *argument, t_expand *curr, t_helper *hp);
void		expand_string(char **string, t_helper *hp, int fromherdoc);
void		argv_expander(char ***argv, t_expand **expandArr, t_helper *hp);
void		print_ast(t_tree *node, int depth, const char *relation);
void		ambiguous_redirect(char *file);
int			is_builtin(char *cmd);
int			exec_builtin(char **argv, char **arg_cpy, t_helper *hp);
void		process_herdocs(t_helper *hp, int left);
void		print_cd_error(char *path);
int			get_last_in(t_redir *redirection, t_redir **last_in,
				int *error_found, t_ambiguous_err	*err);
void		iterate_output_redirection(t_redir *redirection,
				t_redir **last_out, int *error_found);
void		redir_input(t_helper *hp, t_hredir *hr, int *error_found);
void		redir_output(t_redir	*last_out, int *error_found);
int			is_ambiguous(char **expanded, int empty_flag);
void		open_output_error(t_redir *redirection, int error_index,
				int *error_found);
void		subshell_worker(t_helper hp_cpy);
void		subshell_handler(t_helper *hp, pid_t pid);
char		*extract_key(char *str);
int			matches_pattern(const char *filename, const char *pattern);
int			count_matching_files(const char *pattern, int *count);
char		**split_arg(char *new_arg, t_expand *cp, t_helper *hp);

/*  Garbage Collector */
void		*maroc(size_t size, int flag, int type);
int			fdmaroc(char *filename, int type, int flag, int flags);
void		expand_wildcard(char ***argv, bool *wildcards);
int			contain_wildcard(char **argv, bool *wildcards);

// libft
int			ft_handle_overflow(unsigned long nbr, int ndigit, int sign);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_is_alnum(int c);
int			ft_isprint(int c);
int			ft_isnum(char c);
size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set, int type);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t nmemb, size_t size, int type);
char		*ft_strdup(const char *s, int type);
char		*ft_strjoin(char const *s1, char const *s2, int type);
char		**ft_split(char const *s, char c, int type);
char		*ft_itoa(int n, int type);
int			ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_putstrn_fd(char *s, int fd, int n);
int			ft_putnchar_fd(char c, int fd, int n);
char		*ft_substr(char const *s, unsigned int start, size_t len, int type);

# ifndef MAX_FILES_OPENED
#  define MAX_FILES_OPENED 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

#endif
