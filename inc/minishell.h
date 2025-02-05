/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:11:42 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/04 16:09:32 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <readline/readline.h>
# include <stdio.h>

# define OPEN_PARENTH 40
# define CLOSE_PARENTH 41

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
	t_token_type	type;
	int				visited;
	int				for_heredoc;
	int				heredocfd;
	int				spaceafter;
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
	int				spaceafter;  // Space handling
	int				expand;      // Expansion flag (for `$VAR`)
	struct s_args	*next;       // Next argument
}				t_args;

/* helper.c */
int		isspace(char c);
int		isquote(char c);
int		special_d(char c);
int		isparenthesis(char c);
int		isalnum(char c);

t_token	*init_token(void);
int		before_space(char *str, int i);

/* parsing_type.c */
void	ft_space(t_vars **vars, int *ret);
void	parse_char(t_token **token, t_vars **vars, int *ret);
void	parse_quote(t_token **token, t_vars **vars, int *ret);
void	parse_dollar(t_token **token, t_vars **vars, int *ret);
void	parse_separator(t_token **token, t_vars **vars, int *ret);

# endif
