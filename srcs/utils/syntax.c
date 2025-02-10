/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:18:10 by yslami            #+#    #+#             */
/*   Updated: 2025/02/09 17:43:49 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	print_syntax_error(char *token);
static int	check_brackets(t_token *token);
static int	check_redirections(t_token *token);
static int	check_operators(t_token *token);

int	check_syntax(t_token **token)
{
	t_token	*curr;

	if (!token || !*token)
		return (1);
	if (!check_brackets(*token))
		return (0);
	curr = *token;
	while (curr)
	{
		if (curr->type == REDIR_IN || curr->type == REDIR_OUT || \
			curr->type == REDIR_APPEND || curr->type == HEREDOC)
		{
			if (!check_redirections(curr))
				return (0);
		}
		else if (curr->type == PIPE || curr->type == AND || curr->type == OR)
		{
			if (!check_operators(curr))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

static int	print_syntax_error(char *token)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    ft_putendl_fd(token, 2);
    return (0);
}

static int	check_brackets(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == OPEN_BRACKET)
			count++;
		else if (token->type == CLOSED_BRACKET)
		{
			count--;
			if (count < 0)
				return (print_syntax_error(")"));
		}
		token = token->next;
	}
	if (count > 0)
		return (print_syntax_error("("));
	return (1);
}

static int	check_redirections(t_token *token)
{
	if (!token->next || token->next->type != EXPR)
	{
		if (token->type == REDIR_IN)
			return (print_syntax_error("<"));
		else if (token->type == REDIR_OUT)
			return (print_syntax_error(">"));
		else if (token->type == REDIR_APPEND)
			return (print_syntax_error(">>"));
		else if (token->type == HEREDOC)
			return (print_syntax_error("<<"));
	}
	return (1);
}

static int	check_operators(t_token *token)
{
	if (!token->prev || !token->next)
	{
		if (token->type == PIPE)
			return (print_syntax_error("|"));
		else if (token->type == AND)
			return (print_syntax_error("&&"));
		else if (token->type == OR)
			return (print_syntax_error("||"));
	}
	if (token->prev && (token->prev->type == PIPE || \
		token->prev->type == AND || token->prev->type == OR))
		return (print_syntax_error(token->value));
	return (1);
}
