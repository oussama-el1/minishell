/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:05:21 by yslami            #+#    #+#             */
/*   Updated: 2025/02/10 20:52:40 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*skip_parenthesis_back(t_token *token)
{
	int	nb_parenthesis;

	if (token && token->type == CLOSED_BRACKET)
	{
		nb_parenthesis = 1;
		token = token->prev;
		while (token && token->visited != 1 && nb_parenthesis)
		{
			if (token->type == OPEN_BRACKET)
				nb_parenthesis -= 1;
			if (token->type == CLOSED_BRACKET)
				nb_parenthesis += 1;
			if (!nb_parenthesis)
				break ;
			token = token->prev;
		}
	}
	return (token);
}

static enum e_tree_type	tree_type(int type)
{
	if (type == AND)
		return (T_AND);
	else if (type == OR)
		return (T_OR);
	else if (type == PIPE)
		return (T_PIPE);
	else if (type == REDIR_IN)
		return (T_REDIR_IN);
	else if (type == REDIR_OUT)
		return (T_REDIR_OUT);
	else if (type == REDIR_APPEND)
		return (T_REDIR_APPEND);
	else if (HEREDOC)
		return (T_HEREDOC);
	else
		return (T_CMD);
}

t_tree	*create_tree_node(t_token *token, int visit_flag)
{
	t_tree	*node;

	node = malloc(sizeof(node));
	node->data = ft_strdup(token->value);
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	node->tree_type = tree_type(token->type);
	if (visit_flag)
		token->visited = 1;
	return (node);
}
