/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:40:05 by yslami            #+#    #+#             */
/*   Updated: 2025/03/02 23:08:49 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	maroc_free(t_gc_manager **manager, int flag, int type);
static void	full_freemaroc(t_gc_manager **manager);
static void	init_gc_manager(t_gc_manager	**manager);
static void	append_ptrnode(t_gc_manager *manager, void *ptr, int type);

void	*maroc(size_t size, int flag, int type)
{
	static t_gc_manager	*gc_manager = NULL;
	void				*ptr;

	init_gc_manager(&gc_manager);
	if (flag == ALLOC)
	{
		ptr = malloc(size);
		if (!ptr)
			return (ft_exit(NULL), NULL);
	}
	if (flag == FREE || flag == FULLFREE)
		return (maroc_free(&gc_manager, flag, type), NULL);
	append_ptrnode(gc_manager, ptr, type);
	return (ptr);
}

static void	append_ptrnode(t_gc_manager *manager, void *ptr, int type)
{
	t_gc		*new;
	static t_gc	*last;

	new = malloc(sizeof(t_gc));
	if (!new)
		return (ft_exit(NULL), (void)0);
	new->mallocedptr = ptr;
	new->type = type;
	new->next = NULL;
	new->prev = last;
	if (last)
		last->next = new;
	last = new;
	if (!manager->first_iter)
	{
		manager->gc = new;
		manager->first_iter = 1;
	}
}

static void	init_gc_manager(t_gc_manager **manager)
{
	if (!*manager)
	{
		*manager = malloc(sizeof(t_gc_manager));
		if (!*manager)
			ft_exit(NULL);
		(*manager)->gc = NULL;
		(*manager)->first_iter = 0;
	}
}

static void	maroc_free(t_gc_manager **manager, int flag, int type)
{
	t_gc	*curr;

	if (flag == FULLFREE)
		full_freemaroc(manager);
	else
	{
		curr = (*manager)->gc;
		while (curr->next)
			curr = curr->next;
		while (curr)
		{
			if (curr->type == type && curr->mallocedptr)
			{
				free(curr->mallocedptr);
				curr->mallocedptr = NULL;
			}
			curr = curr->prev;
		}
	}
}

static void	full_freemaroc(t_gc_manager **manager)
{
	t_gc	*curr;
	t_gc	*tmp;
	void	*tmp_ptr;

	if (!*manager)
		return ;
	curr = (*manager)->gc;
	while (curr && curr->next)
		curr = curr->next;
	while (curr)
	{
		tmp = curr;
		tmp_ptr = curr->mallocedptr;
		curr = curr->prev;
		free(tmp);
		free(tmp_ptr);
	}
	if (*manager)
		free(*manager);
}
