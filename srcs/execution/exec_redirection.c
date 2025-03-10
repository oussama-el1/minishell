/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:43:35 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/10 23:51:28 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ambiguous_err	*expand_filnames_helper(t_redir *redirection,
				t_ambiguous_err **err, t_helper *hp, int i)
{
	char	**expanded;

	expanded = expand_one_arg(redirection->filename,
			redirection->expand_list, *hp->env, hp->exit_status);
	if (!is_ambiguous(expanded, redirection->filename[0] == '\0'))
		redirection->filename = expanded[0];
	else
	{
		(*err)->filename = redirection->filename;
		(*err)->index = i;
		return (*err);
	}
	return (NULL);
}

t_ambiguous_err	*expand_filnames(t_redir *redirection, t_helper *hp)
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
					redirection->expand_list, *hp->env, hp->exit_status);
			redirection->heredoc_delim = expanded[0];
		}
		else
		{
			if (expand_filnames_helper(redirection, &err, hp, i))
				return (err);
		}
		i++;
		redirection = redirection->next;
	}
	return (NULL);
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
		iterate_output_redirection(hp->node->args->redir, &hr->last_out, &error_found);
	if (!error_found && ((hr->last_in || hp->node->args->herdoc_file) || g_signal_info.skip_herdoc))
		redir_input(hp, hr, &error_found);
	if (error_found)
		res = 1;
	else if (hp->node->type == T_CMD && hp->node->args->argv[0])
		res = exec_command(hp->node, hp->env, hp->exit_status);
	if (hp->node->type != T_SUBSHELL)
		clean_resources(hp, saved_in, saved_out);
	return (res);
}

int	redirect_and_exec(t_helper *hp)
{
	int				error_found;
	int				error_index;
	t_hredir		redir_h;
	t_ambiguous_err	*err;

	err = NULL;
	error_found = 0;
	if (hp->node->args->redir)
		err = expand_filnames(hp->node->args->redir, hp);
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
