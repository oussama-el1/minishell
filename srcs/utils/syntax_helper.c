/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:28:01 by yslami            #+#    #+#             */
/*   Updated: 2025/02/13 19:02:50 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putendl_fd(token, 2);
	return (0);
}

int	check_brackets(t_token *token)
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

void	while_ft(t_token **token, t_token **last, t_syntax *syntax)
{
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
