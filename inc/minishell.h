/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:11:42 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/13 21:50:42 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <readline/readline.h>
# include <stdio.h>

# define OPEN_PARENTH 40
# define CLOSE_PARENTH 41

extern int g_exit_status;
extern int g_received_signal;

enum e_token_type
{
	EXPR,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	PIPE,
	AND,
	OR,
	SPACE,
	D_Q,
	S_Q,
	DOLLAR,
	OPEN_BRACKET,
	CLOSED_BRACKET,
} ;

typedef enum e_tree_type
{
	T_CMD,
	T_AND,
	T_OR,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_REDIR_APPEND,
	T_SUBSHELL,
} t_tree_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

typedef struct s_vars
{
	char			*cmd;
	int				flag;
	int				tmp;
	int				i;
	t_env			*env;
}				t_vars;

typedef struct s_token_map
{
	const char			*key;
	enum e_token_type	type;
}	t_token_map;

typedef struct s_token
{
	char			*value;
	int				type;
	int				visited;
	int				bef_space;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;



typedef struct s_tree
{
	t_tree_type type;
	char **argv;
	char *filename;
	char *heredoc_delim;
	int is_subshell;
	struct s_tree *left;
	struct s_tree *right;
} t_tree;


typedef struct s_joinheredoc
{
	char	*buffer;
	int		flag;
	int		bef_space;
	int		heredoc_flag;
}	t_joinheredoc;

typedef struct s_syntax
{
	int		inside_brackets;
	int		bracket_level;
	t_token	*start;
	t_token	*next_after;
}	t_syntax;

/* helper.c && helper2.c && string_utils.c && list_utils.c */
int		is_space(char c);
int		only_spaces(char *str);
int		isquote(char c);
int		special_d(char c);
int		isparenth(char c);
int		is_alnum(char c);
int		special_d_1(char c);
int	is_dilim(enum e_token_type type);
char	*remove_quotes(char *str);
int		get_type(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
// char 	*ft_substr(char *str, int start, int len);
t_token	*last_token(t_token *token);


/* syntax_helper.c */
int		print_syntax_error(char *token);
int		check_brackets(t_token *token);
void	while_ft(t_token **token, t_token **last, t_syntax *syntax);

t_token	*init_token(void);
int		before_space(char *str, int i);

void	process_input(char *line, t_token **token, t_env *env_list);
void	init_vars(t_vars **vars, char *line, t_env *env_list);
void	ft_newnode(t_token **token, char *value, int before_space);

// /* parsing_type.c && parser.c */
void	ft_space(t_vars **vars, int *ret);
void	parse_char(t_token **token, t_vars **vars, int *ret);
int		parse_quote(t_token **token, t_vars **vars, int *ret);
void	parse_dollar(t_token **token, t_vars **vars, int *ret);
void	parse_separator(t_token **token, t_vars **vars, int *ret);
void	parse_parenthesis(t_token **token, t_vars **vars, int *ret);
int		check_syntax(t_token *token, int inside_brackets);
void	process_tokens(t_token *tken);
// char	*ft_substr(const char *str, unsigned int start, size_t len);

t_token	*join_heredocargs(t_token *token);

/* tree.c */
t_tree *build_ast(t_token *token);


// env_utils
t_env	*init_env(char **envp);
void	add_env_var(t_env **env, char *key,
		char *value, int exported);
void	print_export(t_env *env, int declare);
void	print_env(t_env *env);
int		unset_env_var(t_env **env, char *key);
char	*get_env_var(t_env *env, char *key);
void	set_env_var(t_env **env, char *key, char *value, int exported);
void	free_env(t_env *env);
char	**get_env_array(t_env *env);
t_env	*dup_env(t_env *original);
int		set_name_and_value(char *env, char **name,
		char **value);

# endif
