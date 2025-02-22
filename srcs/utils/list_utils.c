/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:50:44 by yslami            #+#    #+#             */
/*   Updated: 2025/02/19 14:54:09 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*init_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));// malloc is a custom malloc function
	token->value = NULL;
	token->bef_space = 0;
	token->visited = 0;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

void	init_vars(t_vars **vars, char *line, t_env *env_list)
{
	*vars = (t_vars *)malloc(sizeof(t_vars));
	(*vars)->cmd = line;
	(*vars)->env = env_list;
	(*vars)->i = 0;
	(*vars)->flag = 1;
}

void	ft_newnode(t_token **token, char *value, int before_space)
{
	t_token	*new_node;
	t_token	*curr;

	curr = *token;
	new_node = (t_token *)malloc(sizeof(t_token));
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
		token->type != OPEN_BRACKET)// added
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
		new = init_token();
		new->value = ft_strdup(token->value);
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
