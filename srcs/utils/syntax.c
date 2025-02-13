/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:18:10 by yslami            #+#    #+#             */
/*   Updated: 2025/02/13 21:49:22 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_redirections(t_token *token);
static int	check_operators(t_token *token);
static int	handle_bracket_content(t_token **curr, t_syntax *syntax);
static int	handle_special_tokens(t_token *curr);

int	check_syntax(t_token *token, int inside_brackets)
{
	t_token		*curr;
	t_syntax	syntax;

	if (!token)
		return (1);
	if (!inside_brackets && !check_brackets(token))
		return (0);
	curr = token;
	syntax.inside_brackets = inside_brackets;
	while (curr)
	{
		if (curr->type == OPEN_BRACKET)
		{
			if (!handle_bracket_content(&curr, &syntax))
				return (0);
		}
		else if (!handle_special_tokens(curr))
			return (0);
		curr = curr->next;
	}
	return (1);
}

static int	check_operators(t_token *token)
{
	if ((!token->prev || !token->next) && is_dilim(token->type))
		return (print_syntax_error(token->value));
	if (token->prev && is_dilim(token->prev->type))
		return (print_syntax_error(token->value));
	return (1);
}

static int	check_redirections(t_token *token)
{
	if (!token->next || token->next->type != EXPR)
		return (print_syntax_error(token->value));
	token = token->next;
	if (token->type == REDIR_IN || token->type == REDIR_OUT || \
		token->type == REDIR_APPEND || token->type == HEREDOC)
		return (print_syntax_error(token->value));
	return (1);
}

static int	handle_bracket_content(t_token **curr, t_syntax *syntax)
{
	t_token	*token;
	t_token	*last;

	token = *curr;
	if (token && token->prev && !is_dilim(token->prev->type) && \
		token->next)
		return (print_syntax_error(token->next->value));
	token = token->next;
	if (!token || token->type == CLOSED_BRACKET)
		return (print_syntax_error("("));
	syntax->start = token;
	syntax->start->prev = NULL;
	syntax->bracket_level = 1;
	last = token;
	while_ft(&token, &last, syntax);
	if (!token || syntax->bracket_level > 0)
		return (print_syntax_error("("));
	syntax->next_after = token->next;
	last->next = NULL;
	if (!check_syntax(&syntax->start, 1))
		return (0);
	last->next = syntax->next_after;
	*curr = token;
	return (1);
}

static int	handle_special_tokens(t_token *curr)
{
	if (curr->type == REDIR_IN || curr->type == REDIR_OUT || \
		curr->type == REDIR_APPEND || curr->type == HEREDOC)
		return (check_redirections(curr));
	else if (curr->type == PIPE || curr->type == AND || curr->type == OR)
		return (check_operators(curr));
	return (1);
}
