/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:11:42 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/07 16:14:46 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <readline/readline.h>
# include <stdio.h>

# define OPEN_PARENTH 40
# define CLOSE_PARENTH 41

enum e_tree_type
{
	AND,
	OR,
	PIPE,
	CMD,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR_APPEND,
} t_tree_type;

typedef enum e_token_type
{
	WORD,
	PIPE,       // |
	REDIR_IN,   // <
	REDIR_OUT,  // >
	REDIR_APPEND, // >>
	HEREDOC,    // <<
	ENV_VAR,    // $VAR
	QUOTE,      // " or '
	LOGICAL_AND, // &&
	LOGICAL_OR   // ||
}	t_token_type;

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

/* helper.c */
int		is_space(char c);
int		isquote(char c);
int		special_d(char c);
int		isparenthesis(char c);
int		is_alnum(char c);
int		special_d_1(char c);
// char 	*ft_getstr(char *str, int start, int len);

t_token	*init_token(void);
int		before_space(char *str, int i);

void	process_input(char *line, t_token **token, t_env *env_list);
void	init_vars(t_vars **vars, char *line, t_env *env_list);

/* parsing_type.c */
void	ft_space(t_vars **vars, int *ret);
void	parse_char(t_token **token, t_vars **vars, int *ret);
void	parse_quote(t_token **token, t_vars **vars, int *ret);
void	parse_dollar(t_token **token, t_vars **vars, int *ret);
void	parse_separator(t_token **token, t_vars **vars, int *ret);
void	parse_parenthesis(t_token **token, t_vars **vars, int *ret);

# endif
