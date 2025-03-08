/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:43:35 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/07 00:48:42 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_in(t_redir *redirection, t_redir **last_in, int *error_found, t_ambiguous_err	*err)
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
			if (access(redirection->filename, F_OK | R_OK) == -1)
			{
				if (err)
					file_error_handler(redirection, error_found, err->index <= i, err);
				else
					file_error_handler(redirection, error_found, 0, NULL);
				return (i);
			}
			*last_in = redirection;
			last_in_index = i;
		}
		redirection = redirection->next;
		i++;
	}
	return (last_in_index);
}

void	ambiguous_redirect(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
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
			{
				file_error_handler(redirection, error_found, 0, NULL);
				break ;
			}
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
		fd = open("/tmp/heredoc_tmp", O_RDONLY);\
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

int	is_ambiguous(char **expanded)
{
	int	size;

	size = 0;
	while (expanded[size])
		size++;
	if (size > 1)
		return (1);
	return (0);
}

t_ambiguous_err	*expand_filnames(t_redir *redirection, t_env *env, int exit_status)
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
			expanded = expand_one_arg(redirection->heredoc_delim, redirection->expand_list, env, exit_status);
			redirection->heredoc_delim = expanded[0];
		}
		else
		{
			expanded = expand_one_arg(redirection->filename, redirection->expand_list, env, exit_status);
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

void open_output_error(t_redir *redirection, int error_index, int *error_found)
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
			else
				close(fd);
		}
		i++;
		redirection = redirection->next;
	}
}

int	redirect_and_exec(t_tree *node, t_herdoc *herdoc, t_env **env, int exit_status)
{
	int				saved_in;
	int				saved_out;
	int				error_found;
	int				last_heredoc_index;
	int				last_in_index;
	int				error_index;
	int				res;
	t_redir			*last_in;
	t_redir			*last_out = NULL;
	t_redir			*last_heredoc;
	t_ambiguous_err	*err;

	err = NULL;
	error_found = 0;
	res = 0;
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (node->args->redir)
		err = expand_filnames(node->args->redir, *env, exit_status);
	if (herdoc && herdoc->last_herdoc)
	{
		last_heredoc = herdoc->last_herdoc;
		last_heredoc_index = herdoc->index; 
	}
	else
		last_heredoc_index = get_last_heredoc(node->args->redir, &last_heredoc, exit_status, *env);
	last_in_index = get_last_in(node->args->redir, &last_in, &error_found, err);

	error_index = last_in_index;
	if (err)
	{
		error_found = 1;
		if (err->index < last_in_index || last_in_index == -1)
		{
			error_index = err->index;
			ambiguous_redirect(err->filename);
		}
	}
	if (error_found)
		open_output_error(node->args->redir, error_index, &error_found);
	else
		iterate_output_redirection(node->args->redir, &last_out, &error_found);
	if (!error_found && (last_in || last_heredoc))
		redir_input(last_heredoc_index, last_in_index, &error_found, last_in);
	if (last_out && !error_found)
		redir_output(last_out, &error_found);
	if (error_found)
		res = 1;
	else if (node->type == T_CMD && node->args->argv[0])
		res = exec_command(node, env, exit_status);
	if (node->type != T_SUBSHELL)
		clean_resources(saved_in, saved_out);
	return (res);
}
