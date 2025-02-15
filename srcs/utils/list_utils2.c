/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:51 by yslami            #+#    #+#             */
/*   Updated: 2025/02/14 14:06:44 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*sublist(t_token *start, t_token *end)
{
	t_token	*head;
	t_token	*tail;
	t_token *new;

	head = NULL;
	tail = NULL;
	while(start)
	{
		new = init_token();
		new->value = ft_strdup(start->value);
		new->type = start->type;
		new->bef_space = start->bef_space;
		new->visited = start->visited;
		new->prev =tail;
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		if (start == end)
			break ;
		start = start->next;
	}
	return (head);
}
