/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:51 by yslami            #+#    #+#             */
/*   Updated: 2025/02/21 15:54:26 by yslami           ###   ########.fr       */
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

char	*quoted_process(t_token **curr)
{
	char	*tmp;
	char	*arg;

	arg = NULL;
	while (*curr && (*curr)->visited != 1 && non_control((*curr)->type))
	{
		tmp = (*curr)->value;
		if (is_quote((*curr)->type))
			tmp = remove_quote(*curr, tmp);
		if (arg && !(*curr)->bef_space)
			arg = ft_strjoin(arg, tmp);
		else
			arg = ft_strdup(tmp);
		*curr = (*curr)->next;
		if (!*curr || (*curr)->visited == 1 || (*curr)->bef_space == 1)
			break ;
	}
	return (arg);
}


char *remove_quote(t_token *curr, char *str)
{
	char	*res;

	if (curr && curr->type == D_Q)
		res = ft_strtrim(str, "\"");
	else
		res = ft_strtrim(str, "'");
	return (res);
}
