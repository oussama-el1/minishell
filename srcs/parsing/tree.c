/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:07:45 by yslami            #+#    #+#             */
/*   Updated: 2025/03/04 21:22:37 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*build_ast(t_token *token)
{
	t_token	*curr;
	t_token	*save;

	curr = last_token(token);
	while (curr && curr->visited != 1)
	{
		skip_brackets_prev(&curr);
		save = curr;
		if (curr && curr->visited != 1 && curr->type == OPEN_BRACKET)
			curr = curr->prev;
		if (curr && curr->visited != 1 && islogical(curr->type))
			return (found_logical(curr));
		if (curr)
			curr = curr->prev;
	}
	return (fetch_pipe_or_subshell(save));
}

t_tree	*fetch_pipe_or_subshell(t_token *token)
{
	t_token	*curr;
	int		bracket;

	curr = token;
	bracket = 0;
	while (curr && curr->visited != 1)
	{
		skip_brackets_next(&curr, &bracket);
		if (curr && curr->visited != 1 && curr->type == PIPE)
			return (found_pipe(curr, bracket));
		if (curr)
			curr = curr->next;
	}
	if (bracket)
		return (create_subshell(token));
	return (create_cmd(token));
}

t_tree	*found_logical(t_token *token)
{
	t_tree	*node;

	node = create_node(token);
	node->right = fetch_pipe_or_subshell(token->next);
	node->left = build_ast(back_prev(token->prev));
	return (node);
}

t_tree	*found_pipe(t_token *token, int subshell)
{
	t_tree	*node;

	node = create_node(token);
	node->right = fetch_pipe_or_subshell(token->next);
	if (!subshell)
		node->left = create_cmd(left_back(token->prev));
	else
		node->left = create_subshell(token->prev);
	return (node);
}

t_tree	*create_node(t_token *token)
{
	t_tree	*node;

	if (!token)
		return (NULL);
	node = (t_tree *)maroc(sizeof(t_tree), ALLOC, CMD);
	node->type = get_tree_type(token->type);
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	token->visited = 1;
	return (node);
}
