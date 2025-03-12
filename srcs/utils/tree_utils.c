/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:05:21 by yslami            #+#    #+#             */
/*   Updated: 2025/03/12 04:07:07 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_count(t_token *token)
{
	t_token	*curr;
	int		arg_count;

	curr = token;
	arg_count = 0;
	while (curr && curr->visited != 1)
	{
		while (curr && curr->next && !curr->next->bef_space && \
			!isredirect(curr->next->type) && !isredirect(curr->type))
			curr = curr->next;
		if (curr && isredirect(curr->type))
		{
			curr = curr->next;
			while (curr && curr->next && !curr->next->bef_space && \
			!isredirect(curr->next->type) && !isredirect(curr->type))
				curr = curr->next;
		}
		else
			arg_count++;
		if (curr)
			curr = curr->next;
	}
	return (arg_count);
}

t_token	*back_prev(t_token *token)
{
	while (token && token->prev && token->prev->visited != 1)
		token = token->prev;
	return (token);
}

t_token	*left_back(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr && curr->visited != 1 && curr->prev && \
		curr->prev->visited != 1)
	{
		curr = curr->prev;
	}
	return (curr);
}

void	skip_brackets_prev(t_token **token)
{
	int	level;

	if ((*token)->type == CLOSED_BRACKET)
	{
		level = 1;
		(*token) = (*token)->prev;
		while ((*token) && (*token)->visited != 1 && level)
		{
			if ((*token)->type == OPEN_BRACKET)
				level--;
			else if ((*token)->type == CLOSED_BRACKET)
				level++;
			if (!level)
				break ;
			(*token) = (*token)->prev;
		}
	}
}

void	skip_brackets_next(t_token **token, int *has_brackets)
{
	int	level;

	if ((*token) && (*token)->type == OPEN_BRACKET)
	{
		(*token)->visited = 1;
		level = 1;
		if (has_brackets)
			*has_brackets = 1;
		(*token) = (*token)->next;
		while ((*token) && (*token)->visited != 1 && level)
		{
			if ((*token)->type == OPEN_BRACKET)
				level++;
			else if ((*token)->type == CLOSED_BRACKET)
				level--;
			if (!level)
				break ;
			(*token) = (*token)->next;
		}
		if (*token && (*token)->type == CLOSED_BRACKET)
			(*token)->visited = 1;
	}
}
