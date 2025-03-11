/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_helpers2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:05:01 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/11 20:50:01 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_expand_herdoc(t_helper *hp, int fd, int *error_found)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		*error_found = 1;
		return (close(fd), (void)0);
	}
	line = get_next_line(fd);
	while (line)
	{
		expand_string(&line, *(hp->env), hp->exit_status, 1);
		write(pipe_fd[1], line, ft_strlen(line));
		line = get_next_line(fd);
	}
	close(fd);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

void	redir_input(t_helper *hp, t_hredir *hr, int *error_found)
{
	int	fd;

	fd = -1;
	if ((hp->node->args->herdoc_idx > hr->last_in_idx))
		fd = open(hp->node->args->herdoc_file, O_RDONLY);
	else if (hr->last_in)
		fd = open(hr->last_in->filename, O_RDONLY);
	if (fd == -1)
	{
		*error_found = 1;
		return ;
	}
	if ((hp->node->args->herdoc_idx > hr->last_in_idx))
		read_expand_herdoc(hp, fd, error_found);
	else if (fd >= 0)
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

int	get_last_heredoc(t_redir *redirection, t_helper *hp)
{
	int		i;

	i = 0;
	hp->node->args->herdoc_idx = -1;
	hp->node->args->herdoc_file = NULL;
	while (redirection && !g_signal_info.skip_herdoc)
	{
		if (redirection->type == R_HEREDOC)
		{
			if (!redirection->next)
			{
				hp->node->args->herdoc_file = \
					handle_heredoc(redirection->heredoc_delim, hp, 0);
				hp->node->args->herdoc_idx = i;
			}
			else
				handle_heredoc(redirection->heredoc_delim, hp, 1);
		}
		redirection = redirection->next;
		i++;
	}
	return (hp->node->args->herdoc_idx);
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
