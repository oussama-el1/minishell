/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 04:35:59 by yslami            #+#    #+#             */
/*   Updated: 2025/03/12 07:14:08 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_fdnode(t_fd_gc	**head, int fd, char *filename, int type);
static void	fdmaroc_free(t_fd_gc **head);

int	fdmaroc(char *filename, int type, int flag, int flags)
{
	static t_fd_gc	*head = NULL;
	int				fd;

	if (flag == OPEN)
	{
		if (type == REDIR_OUT || type == HEREDOC)
			fd = open(filename, flags, 0644);
		if (type == REDIR_IN)
			fd = open(filename, flags);
		if (fd < 0)
			return (-1);
		append_fdnode(&head, fd, filename, type);
		return (fd);
	}
	if (flag == CLEAR)
		return (fdmaroc_free(&head), -1);
	return (-1);
}

static void	append_fdnode(t_fd_gc	**head, int fd, char *filename, int type)
{
	t_fd_gc			*new;
	static t_fd_gc	*last = NULL;

	new = maroc(sizeof(t_fd_gc), ALLOC, CMD);
	new->fd = fd;
	new->type = type;
	new->filename = filename;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		last = *head;
		return ;
	}
	last->next = new;
	last = new;
}

static void	fdmaroc_free(t_fd_gc **head)
{
	t_fd_gc	*curr;
	t_fd_gc	*tmp;

	curr = *head;
	while (curr)
	{
		tmp = curr;
		close(curr->fd);
		if (curr->type == HEREDOC)
			unlink(curr->filename);
		curr = curr->next;
		free(tmp);
	}
	*head = NULL;
}
