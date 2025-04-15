/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:16:50 by yslami            #+#    #+#             */
/*   Updated: 2025/03/13 20:10:00 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_type	get_redir_type(int type);
static void			append_redir_node(t_redir **redir_list, t_redir *new_redir);
static t_redir		*create_redir_node(int type, char *filename, \
	t_expand *expand_list);

void	handle_redirection(t_redir **redir_list, t_token **curr)
{
	t_redir		*new_redir;
	t_expand	*expand_list;
	char		*filename;
	int			type;

	if (!curr || !(*curr) || !isredirect((*curr)->type))
		return ;
	expand_list = NULL;
	type = (*curr)->type;
	*curr = (*curr)->next;
	if (*curr)
	{
		filename = quoted_process(curr, &expand_list, 0);
		new_redir = create_redir_node(type, filename, expand_list);
		if (new_redir)
			append_redir_node(redir_list, new_redir);
	}
}

static void	append_redir_node(t_redir **redir_list, t_redir *new_redir)
{
	t_redir	*curr;

	if (!*redir_list)
	{
		*redir_list = new_redir;
		return ;
	}
	curr = *redir_list;
	while (curr->next)
		curr = curr->next;
	curr->next = new_redir;
}

static t_redir	*create_redir_node(int type, char *filename, \
	t_expand *expand_list)
{
	t_redir	*new_redir;

	new_redir = (t_redir *)maroc(sizeof(t_redir), ALLOC, CMD);
	new_redir->filename = NULL;
	new_redir->h_del = NULL;
	new_redir->type = get_redir_type(type);
	if (new_redir->type != R_HEREDOC)
		new_redir->filename = filename;
	else
		new_redir->h_del = filename;
	new_redir->expand_list = expand_list;
	new_redir->next = NULL;
	return (new_redir);
}

static t_redir_type	get_redir_type(int type)
{
	if (type == REDIR_IN)
		return (R_REDIR_IN);
	if (type == REDIR_OUT)
		return (R_REDIR_OUT);
	if (type == REDIR_APPEND)
		return (R_REDIR_APPEND);
	return (R_HEREDOC);
}
