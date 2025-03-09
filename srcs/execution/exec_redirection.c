/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:43:35 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/09 02:22:53 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ambiguous_err	*expand_filnames(t_redir *redirection,
				t_env *env, int exit_status)
{
	t_ambiguous_err	*err;
	int				i;
	char			**expanded;

	i = 0;
	err = maroc(sizeof(t_ambiguous_err), ALLOC, CMD);
	while (redirection)
	{
		if (redirection->type == R_HEREDOC)
		{
			expanded = expand_one_arg(redirection->heredoc_delim,
					redirection->expand_list, env, exit_status);
			redirection->heredoc_delim = expanded[0];
		}
		else
		{
			expanded = expand_one_arg(redirection->filename,
					redirection->expand_list, env, exit_status);
			if (!is_ambiguous(expanded))
				redirection->filename = expanded[0];
			else
			{
				err->filename = redirection->filename;
				err->index = i;
				return (err);
			}
		}
		i++;
		redirection = redirection->next;
	}
	return (NULL);
}

void	open_output_error(t_redir *redirection, int error_index,
		int *error_found)
{
	int	fd;
	int	i;

	i = 0;
	while (redirection && i < error_index)
	{
		if ((redirection->type == R_REDIR_OUT
				|| redirection->type == R_REDIR_APPEND))
		{
			if (redirection->type == R_REDIR_OUT)
				fd = open(redirection->filename,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open(redirection->filename,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				file_error_handler(redirection, error_found, 0, NULL);
				break ;
			}
			close(fd);
		}
		i++;
		redirection = redirection->next;
	}
}

static int	redirect_and_exec_helper(t_helper *hp, t_hredir *hr,
	int error_found, int error_index)
{
	int	res;
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	res = 0;
	if (error_found)
		open_output_error(hp->node->args->redir, error_index, &error_found);
	else
		iterate_output_redirection(hp->node->args->redir,
			&hr->last_out, &error_found);
	if (!error_found && ((hr->last_in || hr->last_heredoc) || g_signal_info.skip_herdoc))
		redir_input(hr->last_her_idx, hr->last_in_idx, &error_found, hr->last_in);
	if (hr->last_out && !error_found)
		redir_output(hr->last_out, &error_found);
	if (error_found)
		res = 1;
	else if (hp->node->type == T_CMD && hp->node->args->argv[0])
		res = exec_command(hp->node, hp->env, hp->exit_status);
	if (hp->node->type != T_SUBSHELL)
		clean_resources(saved_in, saved_out);
	return (res);
}

static void	redirect_herdoc(t_helper *hp, t_hredir *redir_h, t_herdoc *herdoc)
{
	if (herdoc && herdoc->last_herdoc)
	{
		redir_h->last_heredoc = herdoc->last_herdoc;
		redir_h->last_her_idx = herdoc->index;
	}
	else
		redir_h->last_her_idx = get_last_heredoc(hp->node->args->redir,
				&redir_h->last_heredoc, hp);
}

int	redirect_and_exec(t_helper *hp, t_herdoc *herdoc)
{
	int				error_found;
	int				error_index;
	t_hredir		redir_h;
	t_ambiguous_err	*err;

	err = NULL;
	error_found = 0;
	if (hp->node->args->redir)
		err = expand_filnames(hp->node->args->redir, *hp->env, hp->exit_status);
	redirect_herdoc(hp, &redir_h, herdoc);
	redir_h.last_in_idx = get_last_in(hp->node->args->redir,
			&redir_h.last_in, &error_found, err);
	error_index = redir_h.last_in_idx;
	if (err)
	{
		if (!error_found || err->index < redir_h.last_in_idx
			|| redir_h.last_in_idx == -1)
		{
			error_index = err->index;
			ambiguous_redirect(err->filename);
		}
		error_found = 1;
	}
	return (redirect_and_exec_helper(hp, &redir_h, error_found, error_index));
}
