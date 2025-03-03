/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:51 by yslami            #+#    #+#             */
/*   Updated: 2025/03/03 00:45:56 by yslami           ###   ########.fr       */
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
		init_token(&new, 1);
		new->value = ft_strdup(start->value, CMD);
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

char	*quoted_process(t_token **curr, t_expand **expansion_list, bool *wildcard)
{
	char		*tmp;
	char		*arg;
	t_expand	*head;
	t_token		*save;
	size_t		start;
	int			level;

	head = NULL;
	arg = NULL;
	start = 0;
	level = 0;
	while (*curr && (*curr)->visited != 1 && non_control((*curr)->type))
	{
		save = *curr;
		if (*curr)
			tmp = (*curr)->value;
		expansion_func(&head, *curr, &tmp, &start);
		if (arg && !(*curr)->bef_space)
			arg = ft_strjoin(arg, tmp, CMD);
		else
			arg = ft_strdup(tmp, CMD);
		start += ft_strlen(tmp);
		*curr = (*curr)->next;
		if (!*curr || (*curr)->visited == 1 || (*curr)->bef_space == 1)
			break ;
		level = 1;
	}
	if (!level && is_wildcard(save) && wildcard)
		*wildcard = true;
	else
	{
		if (wildcard)
			*wildcard = false;
	}
	*expansion_list = head;
	return (arg);
}

char *remove_quote(t_token *curr, char *str)
{
	char	*res;

	if (curr && curr->type == D_Q)
		res = ft_strtrim(str, "\"", CMD);
	else
		res = ft_strtrim(str, "'", CMD);
	return (res);
}

void	expansion_func(t_expand	**head, t_token *curr, char **str, size_t *start)
{
	size_t			end;
	t_expand		*new;
	static t_expand	*tail = NULL;

	if (!curr)
		return ;
	if (is_quote(curr->type))
		*str = remove_quote(curr, *str);
	end = *start + ft_strlen(*str) * (**str != 0);
	new = (t_expand *)maroc(sizeof(t_expand), ALLOC, CMD);
	new->expanded = (curr->type == D_Q || curr->type == DOLLAR);
	new->start = *start;
	new->end = end;
	new->next = NULL;
	new->prev = NULL;
	if (!*head)
		*head = new;
	else
	{
		new->prev = tail;
		tail->next = new;
	}
	tail = new;
}
