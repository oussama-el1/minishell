/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:11:42 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/10 20:42:50 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <readline/readline.h>
# include <stdio.h>

# define OPEN_PARENTH 40
# define CLOSE_PARENTH 41

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

enum e_tree_type
{
	T_CMD,
	T_AND,
	T_OR,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_REDIR_APPEND,
} t_tree_type;

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

typedef struct s_env
{
	char			*key;       // Variable name
	char			*value;     // Variable value
	int				size;       // Size of the environment list
	char			*pwd;       // Current working directory
	int				env_null;   // Flag for empty environment
	struct s_env	*prev;      // Previous variable
	struct s_env	*next;      // Next environment variable
}				t_env;

typedef struct s_vars
{
	char			*cmd;
	int				flag;
	int				tmp;
	int				i;
	t_env			*env;
}				t_vars;

typedef struct s_args
{
	char			*cmd;        // Argument value
	int				bef_space;  // Space handling
	int				expand;      // Expansion flag (for `$VAR`)
	struct s_args	*next;       // Next argument
}				t_args;

typedef struct s_cmd
{
	char			*cmd;
	int				fd[2];
	int				word;
	int				bef_space;
	int				heredocfd;
	int				expandheredoc;
	int				expandwildcard;
	int				ambiguous;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_tree
{
	char				*data; // command name
	int					fd[2]; // file descriptors for pipe
	t_cmd				*next; // next command in the pipe
	struct s_tree		*left; // left child in the tree
	struct s_tree		*right;// right child in the tree
	enum e_tree_type	tree_type; // type of the node
}				t_tree;

typedef struct s_joinheredoc
{
	char	*buffer;
	int		flag;
	int		bef_space;
	int		heredoc_flag;
}	t_joinheredoc;

/* helper.c && helper2.c && string_utils.c */
int		is_space(char c);
int		only_spaces(char *str);
int		isquote(char c);
int		special_d(char c);
int		isparenth(char c);
int		is_alnum(char c);
int		special_d_1(char c);
char	*remove_quotes(char *str);
int		get_type(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
// char 	*ft_substr(char *str, int start, int len);


t_token	*init_token(void);
int		before_space(char *str, int i);

void	process_input(char *line, t_token **token, t_env *env_list);
void	init_vars(t_vars **vars, char *line, t_env *env_list);
void	ft_newnode(t_token **token, char *value, int before_space);

/* parsing_type.c */
void	ft_space(t_vars **vars, int *ret);
void	parse_char(t_token **token, t_vars **vars, int *ret);
int		parse_quote(t_token **token, t_vars **vars, int *ret);
void	parse_dollar(t_token **token, t_vars **vars, int *ret);
void	parse_separator(t_token **token, t_vars **vars, int *ret);
void	parse_parenthesis(t_token **token, t_vars **vars, int *ret);
int		check_syntax(t_token **token);
char	*ft_substr(const char *str, unsigned int start, size_t len);

t_token	*join_heredocargs(t_token *token);

/* tree.c */
t_tree *build_ast(t_token *token);
t_token	*skip_parenthesis_back(t_token *token);
t_tree	*create_tree_node(t_token *token, int visit_flag);

# endif
