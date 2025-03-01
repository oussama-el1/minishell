/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:43:35 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/01 16:14:31 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_last_in(t_redir *redirection, t_redir **last_in, int *error_found)
{
	int	i;
	int	last_in_index;

	i = 0;
	last_in_index = -1;
	*last_in = NULL;
	while (redirection && !*error_found)
	{
		if (redirection->type == R_REDIR_IN)
		{
			if (access(redirection->filename, F_OK) == -1)
				file_error_handler(redirection, error_found);
			else
			{
				*last_in = redirection;
				last_in_index = i;
			}
		}
		redirection = redirection->next;
		i++;
	}
	return (last_in_index);
}

void	iterate_output_redirection(t_redir *redirection,
		t_redir **last_out, int *error_found)
{
	int	fd;

	*last_out = NULL;
	while (redirection && !*error_found)
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
				file_error_handler(redirection, error_found);
			else
			{
				close(fd);
				*last_out = redirection;
			}
		}
		redirection = redirection->next;
	}
}

void	redir_input(int last_heredoc_index, int last_in_index,
		int *error_found, t_redir *last_in)
{
	int	fd;

	fd = -1;
	if (last_heredoc_index > last_in_index)
		fd = open("/tmp/heredoc_tmp", O_RDONLY);
	else if (last_in)
		fd = open(last_in->filename, O_RDONLY);
	if (fd == -1)
	{
		*error_found = 1;
		return ;
	}
	if (fd >= 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2 failed");
			close(fd);
			*error_found = 1;
		}
		close(fd);
	}
}

void	redir_output(t_redir	*last_out, int *error_found)
{
	int	fd;

	if (last_out->type == R_REDIR_OUT)
		fd = open(last_out->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(last_out->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("Output Redirection Failed");
		*error_found = 1;
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 failed");
			close(fd);
			*error_found = 1;
		}
		close(fd);
	}
}

void expand_filnames(t_redir *redirection, t_env *env, int exit_status)
{
	while (redirection)
	{
		if (redirection->type == R_HEREDOC)
			expand_one_arg(&redirection->heredoc_delim, redirection->expand_list, env, exit_status);
		else
			expand_one_arg(&redirection->filename, redirection->expand_list, env, exit_status);
		redirection = redirection->next;
	}
}

int	redirect_and_exec(t_tree *node, t_env *env, int exit_status)
{
	int		saved_in;
	int		saved_out;
	int		error_found;
	int		last_heredoc_index;
	int		last_in_index;
	int		res;
	t_redir	*last_in;
	t_redir	*last_out;
	t_redir	*last_heredoc;

	error_found = 0;
	res = 0;
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	expand_filnames(node->args->redir, env, exit_status);
	last_heredoc_index = get_last_heredoc(node->args->redir,
			&last_heredoc, exit_status, env);
	last_in_index = get_last_in(node->args->redir, &last_in, &error_found);
	iterate_output_redirection(node->args->redir, &last_out, &error_found);
	if (!error_found && (last_in || last_heredoc))
		redir_input(last_heredoc_index, last_in_index, &error_found, last_in);
	if (last_out && !error_found)
		redir_output(last_out, &error_found);
	if (error_found)
		res = 1;
	else if (node->type == T_CMD)
		res = exec_command(node, env, exit_status);
	if (node->type != T_SUBSHELL)
		clean_resources(saved_in, saved_out);
	return (res);
}
