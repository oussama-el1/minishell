/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_helpers2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:05:01 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/09 02:27:26 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_input(int last_heredoc_index, int last_in_index,
		int *error_found, t_redir *last_in)
{
	int	fd;

	fd = -1;
	if ((last_heredoc_index > last_in_index) || (g_signal_info.skip_herdoc))
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

int	get_last_heredoc(t_redir *redirection, t_redir **last_heredoc, t_helper *hp)
{
	int	i;
	int	last_heredoc_index;

	i = 0;
	last_heredoc_index = -1;
	*last_heredoc = NULL;
	while (redirection && !g_signal_info.skip_herdoc)
	{
		if (redirection->type == R_HEREDOC)
		{
			handle_heredoc(redirection->heredoc_delim, hp);
			*last_heredoc = redirection;
			last_heredoc_index = i;
		}
		redirection = redirection->next;
		i++;
	}
	return (last_heredoc_index);
}

int	get_last_in(t_redir *redirection, t_redir **last_in,
	int *error_found, t_ambiguous_err	*err)
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
					return (file_error_handler(redirection, error_found,
							err->index <= i, err), i);
				return (file_error_handler(redirection,
						error_found, 0, NULL), i);
			}
			*last_in = redirection;
			last_in_index = i;
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
				return (file_error_handler(redirection,
						error_found, 0, NULL), (void)0);
			else
			{
				close(fd);
				*last_out = redirection;
			}
		}
		redirection = redirection->next;
	}
}
