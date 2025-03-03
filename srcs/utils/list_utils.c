/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:50:44 by yslami            #+#    #+#             */
/*   Updated: 2025/03/02 23:41:55 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_token(t_token **token, int create)
{
	if (create)
		*token = (t_token *)maroc(sizeof(t_token), ALLOC, CMD);
	(*token)->value = NULL;
	(*token)->bef_space = 0;
	(*token)->visited = 0;
	(*token)->prev = NULL;
	(*token)->next = NULL;
}

void	init_vars(t_vars **vars, char *line)
{
	*vars = (t_vars *)maroc(sizeof(t_vars), ALLOC, CMD);
	(*vars)->cmd = line;
	(*vars)->i = 0;
	(*vars)->flag = 1;
}

void	ft_newnode(t_token **token, char *value, int before_space)
{
	t_token	*new_node;
	t_token	*curr;

	curr = *token;
	new_node = (t_token *)maroc(sizeof(t_token), ALLOC, CMD);
	new_node->value = value;
	new_node->visited = 0;
	new_node->bef_space = before_space;
	new_node->next = NULL;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
	new_node->prev = curr;
}

t_token	*last_token(t_token *token)
{
	if (!token)
		return (NULL);
	if (token && token->visited == 1 && \
		token->type != OPEN_BRACKET)
		return (token->prev);
	while (token->next && token->next->visited != 1)
		token = token->next;
	return (token);
}

t_token	*lst_dup(t_token *token)
{
	t_token	*head;
	t_token	*tail;
	t_token *new;

	head = NULL;
	tail = NULL;
	while(token)
	{
		init_token(&new, 1);
		new->value = ft_strdup(token->value, CMD);
		new->type = token->type;
		new->bef_space = token->bef_space;
		new->visited = token->visited;
		new->prev = tail;
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		token = token->next;
	}
	return (head);
}
