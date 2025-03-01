/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:28:01 by yslami            #+#    #+#             */
/*   Updated: 2025/03/01 17:50:38 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_operators(t_token *token)
{
	if (is_dilim(token->type) && (!token->prev))
		return (print_syntax_error(token->value));
	if (token->next && is_dilim(token->type) && \
		is_dilim(token->next->type))
		return (print_syntax_error(token->next->value));
	if (token->next && token->next->type == CLOSED_BRACKET)
		return (print_syntax_error(token->next->value));
	return (1);
}

int	check_redirections(t_token *token)
{
	if (!token->next || token->next->type == CLOSED_BRACKET || \
		!is_regular(token->next->type))
	{
		if (token->next)
			return (print_syntax_error(token->next->value));
		else
			return (print_syntax_error("newline"));
	}
	token = token->next;
	if (token->type == REDIR_IN || token->type == REDIR_OUT || \
		token->type == REDIR_APPEND || token->type == HEREDOC)
		return (print_syntax_error(token->value));
	return (1);
}

int	check_brackets(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == OPEN_BRACKET)
		{
			count++;
			if (token->next && token->next->type == CLOSED_BRACKET)
				return (print_syntax_error(token->next->value));
		}
		else if (token->type == CLOSED_BRACKET)
		{
			count--;
			if (count < 0)
				return (print_syntax_error(token->value));
		}
		token = token->next;
	}
	if (count > 0)
		return (print_syntax_error("("));
	return (1);
}

void	while_ft(t_token **token, t_token **last, t_syntax *syntax)
{
	syntax->start = *token;
	syntax->bracket_level = 1;
	while (*token && syntax->bracket_level > 0)
	{
		if ((*token)->type == OPEN_BRACKET)
			syntax->bracket_level++;
		else if ((*token)->type == CLOSED_BRACKET)
			syntax->bracket_level--;
		if (syntax->bracket_level > 0)
		{
			*last = *token;
			*token = (*token)->next;
		}
	}
}

int	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putendl_fd(token, 2);
	return (0);
}
