/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:18:10 by yslami            #+#    #+#             */
/*   Updated: 2025/02/22 14:00:52 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_bracket_content(t_token **curr, t_syntax *syntax);
static int	handle_special_tokens(t_token *curr);
static int	check_syntax_1(t_token **token, int inside_brackets);
static int	check_next_closed(t_token *token);

int	check_syntax(t_token *token, int inside_brackets)
{
	t_token	*copy;

	copy = lst_dup(token);
	return (check_syntax_1(&copy, inside_brackets));
}

static int	check_syntax_1(t_token **token, int inside_brackets)
{
	t_token		*curr;
	t_syntax	syntax;

	if (!token || !*token)
		return (1);
	if (!inside_brackets && !check_brackets(*token))
		return (0);
	curr = *token;
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

static int	handle_special_tokens(t_token *curr)
{
	if (curr->type == REDIR_IN || curr->type == REDIR_OUT || \
		curr->type == REDIR_APPEND || curr->type == HEREDOC)
		return (check_redirections(curr));
	else if (curr->type == PIPE || curr->type == AND || curr->type == OR)
		return (check_operators(curr));
	if (contains_unquoted_ampersand(curr->value))
			return (print_syntax_error("&"));
	return (1);
}

static int	handle_bracket_content(t_token **curr, t_syntax *syntax)
{
	t_token	*token;
	t_token	*last;
	t_token	*bracket_list;

	token = *curr;
	if (token && token->prev && !is_dilim(token->prev->type) && token->next)
		return (print_syntax_error(token->next->value));
	token = token->next;
	if (!token || token->type == CLOSED_BRACKET)
		return (print_syntax_error("("));
	last = token;
	while_ft(&token, &last, syntax);
	if (token->type == CLOSED_BRACKET && !check_next_closed(token))
			return (0);
	if (!token || syntax->bracket_level > 0)
		return (print_syntax_error("("));
	bracket_list = sublist(syntax->start, token);
	if (!check_syntax_1(&bracket_list, 1))
		return (0);
	*curr = token;
	return (1);
}

static int	check_next_closed(t_token *token)
{
	t_token	*curr;

	if (token->next && token->next->type != CLOSED_BRACKET && non_control(token->next->type))
		return (print_syntax_error(token->next->value));
	curr = token->next;
	while(curr)
	{
		if (curr->type == EXPR || curr->type == DOLLAR || is_quote(curr->type))
			return (print_syntax_error(curr->value));
		if (curr->type == isredirect(curr->type))
			curr = curr->next;
		if (curr)
			curr = curr->next;
		if (curr && is_dilim(curr->type))
			break ;
	}
	return (1);
}
