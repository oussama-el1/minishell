/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:43:35 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/16 06:01:00 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	iterate_output_redirection(t_redir *redirection,
								t_redir **last_out, int *error_found)
{
	int	fd;

	*last_out = NULL;
	while (redirection && !*error_found)
	{
		if ((redirection->type == R_REDIR_OUT \
				|| redirection->type == R_REDIR_APPEND))
		{
			if (redirection->type == R_REDIR_OUT)
				fd = fdmaroc(redirection->filename, REDIR_OUT,
						OPEN, O_WRONLY | O_CREAT | O_TRUNC);
			else
				fd = fdmaroc(redirection->filename, REDIR_OUT,
						OPEN, O_WRONLY | O_CREAT | O_APPEND);
			if (fd < 0)
				return (file_error_handler(redirection,
						error_found, 0, NULL), (void)0);
			else
				*last_out = redirection;
		}
		redirection = redirection->next;
	}
}

t_ambiguous_err	*expand_filnames_helper(t_redir *redirection,
					t_ambiguous_err **err, t_helper *hp, int i)
{
	char	**expanded;
	int		size;

	size = 0;
	expanded = expand_one_arg(redirection->filename,
			redirection->expand_list, hp, &size, 0);
	if (size == 1)
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

	i = 0;
	err = maroc(sizeof(t_ambiguous_err), ALLOC, CMD);
	while (redirection)
	{
		if (redirection->type != R_HEREDOC
			&& expand_filnames_helper(redirection, &err, hp, i))
			return (err);
		i++;
		redirection = redirection->next;
	}
	return (NULL);
}

static void	redirect_and_exec_helper(t_helper *hp, t_hredir *hr,
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
	if (!error_found && (hr->last_in || hp->node->args->herdoc_file))
		redir_input(hp, hr, &error_found);
	if (!error_found && hr->last_out)
		redir_output(hr->last_out, &error_found);
	if (error_found)
		res = 1;
	else if (hp->node->type == T_CMD && hp->node->args->argv[0])
		res = exec_command(hp->node, hp);
	if (hp->node->type != T_SUBSHELL)
		clean_resources(hp, saved_in, saved_out);
	g_exit_status = res;
}

void	redirect_and_exec(t_helper *hp)
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
	redirect_and_exec_helper(hp, &redir_h, error_found, error_index);
}
