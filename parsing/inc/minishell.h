/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:11:42 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/28 12:56:52 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>

# define OPEN_PARENTH 40
# define CLOSE_PARENTH 41
# define YASSINE 1

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
} t_tree_type;

typedef enum e_redir_type
{
	R_REDIR_IN,
	R_REDIR_OUT,
	R_REDIR_APPEND,
	R_HEREDOC,
} t_redir_type;

enum e_flag
{
	ALLOC,
	FREE,
	FULLFREE,
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
	size_t			start;
	size_t			end;
	struct s_expand	*next;
}	t_expand;

typedef struct s_redir
{
	char			*filename;
	char			*heredoc_delim;
	t_expand		*expand_list;
	t_redir_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_args
{
	char		**argv;
	t_expand	**expand_list;
	t_redir		*redir;
}	t_args;

typedef struct s_tree
{
	t_tree_type		type;
	t_args			*args;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;

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

/* // Garbage Collector
typedef struct s_gc
{
	void		*mallocedptr;
	struct s_gc	*next;
	struct s_gc	*prev;
}	t_gc;

typedef struct s_gc_manager
{
	t_gc	*gc;
	int		first_iter;
}	t_gc_manager;
*/

/* helper.c && helper2.c && string_utils.c && list_utils.c */
int		is_space(char c);
int		empty(char *str);
int		isquote(char c);
int		special_d(char c);
int		isparenth(char c);
int		is_alnum(char c);
int		special_d_1(char c);
int		isredirect(enum e_token_type type);
int		is_dilim(enum e_token_type type);
int		non_control(enum e_token_type type);
int		islogical(enum e_token_type type);
int		is_quote(enum e_token_type type);
int 	is_regular(enum e_token_type type);
char	*remove_quotes(char *str);
int		get_type(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
// char 	*ft_substr(char *str, int start, int len);
t_token	*last_token(t_token *token);
t_token	*lst_dup(t_token *token);
t_token	*sublist(t_token *start, t_token *end);
int		contains_unquoted_ampersand(const char *str);
char 	*remove_quote(t_token *curr, char *str);

/* syntax_helper.c */
int		print_syntax_error(char *token);
int		check_brackets(t_token *token);
void	while_ft(t_token **token, t_token **last, t_syntax *syntax);
int		check_operators(t_token *token);
int		check_redirections(t_token *token);


void	init_token(t_token **token, int allocate);
int		before_space(char *str, int i);

void	process_input(char *line, t_token **token);
void	init_vars(t_vars **vars, char *line);
void	ft_newnode(t_token **token, char *value, int before_space);

// /* parsing_type.c && parser.c */
void	ft_space(t_vars **vars, int *ret);
void	parse_char(t_token **token, t_vars **vars, int *ret);
int		parse_quote(t_token **token, t_vars **vars, int *ret);
void	parse_dollar(t_token **token, t_vars **vars, int *ret);
void	parse_separator(t_token **token, t_vars **vars, int *ret);
void	parse_parenthesis(t_token **token, t_vars **vars, int *ret);
int		check_syntax(t_token *token, int inside_brackets);
// char	*ft_substr(const char *str, unsigned int start, size_t len);

t_token	*join_heredocargs(t_token *token);

/* tree.c */
t_tree 		*build_ast(t_token *token);
t_tree		*fetch_pipe_or_subshell(t_token *token);
t_tree		*found_logical(t_token *token);
t_tree		*found_pipe(t_token *token, int subshell);
t_tree		*create_node(t_token *token);
void		skip_brackets_next(t_token **token, int *has_brackets);
void		skip_brackets_prev(t_token **token);
t_tree		*create_subshell(t_token *token);
t_tree		*create_cmd(t_token *token);
void		extract_args(t_args *args, t_token *token);
t_tree_type get_tree_type(int type);
t_token		*back_prev(t_token *token);
char		*quoted_process(t_token **curr, t_expand **expansion_list);
t_token		*left_back(t_token *token);
int			args_count(t_token *token);
void		expansion_func(t_expand	**head, t_token *curr, char **str, size_t *start);

// redirections
t_redir			*create_redir_node(int type, char *filename);
void			append_redir_node(t_redir **redir_list, t_redir *new_redir);
void			handle_redirection(t_redir **redir_list, t_token **curr);
t_redir_type	get_redir_type(int type);
void 			extract_subshell_args(t_args *args, t_token *token);


# endif
