/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_helpers2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:05:01 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/14 22:26:08 by yslami           ###   ########.fr       */
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
		if (hp->node->args->expnaded)
			expand_string(&line, hp, 1);
		write(pipe_fd[1], line, ft_strlen(line));
		line = get_next_line(fd);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

void	redir_input(t_helper *hp, t_hredir *hr, int *error_found)
{
	int	fd;

	fd = -1;
	if ((hp->node->args->herdoc_idx > hr->last_in_idx))
		fd = fdmaroc(hp->node->args->herdoc_file, HEREDOC, OPEN, O_RDONLY);
	else if (hr->last_in)
		fd = fdmaroc(hr->last_in->filename, REDIR_IN, OPEN, O_RDONLY);
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
			*error_found = 1;
		}
	}
}

void	redir_output(t_redir	*last_out, int *error_found)
{
	int	fd;

	if (last_out->type == R_REDIR_OUT)
		fd = fdmaroc(last_out->filename, REDIR_OUT,
				OPEN, O_WRONLY | O_CREAT | O_TRUNC);
	else
		fd = fdmaroc(last_out->filename, REDIR_OUT,
				OPEN, O_WRONLY | O_CREAT | O_APPEND);
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
			*error_found = 1;
		}
	}
}

int	check_expanded(t_redir *redir)
{
	t_expand	*curr;

	curr = redir->expand_list;
	while (curr)
	{
		if (curr->type == S_Q || curr->type == D_Q)
			return (0);
		curr = curr->next;
	}
	return (1);
}

void	herdoc_runner(t_redir *red, t_helper *hp)
{
	int		i;
	t_redir	*last_herdoc;
	t_redir	*save;

	save = red;
	while (save)
	{
		if (save->type == R_HEREDOC)
			last_herdoc = save;
		save = save->next;
	}
	i = 0;
	hp->node->args->expnaded = 0;
	while (red && !hp->herdoc_sigint)
	{
		if (red == last_herdoc)
		{
			hp->node->args->herdoc_file = handle_heredoc(red->h_del, hp, 0);
			hp->node->args->herdoc_idx = i;
			hp->node->args->expnaded = check_expanded(red);
		}
		else if (red->type == R_HEREDOC)
			handle_heredoc(red->h_del, hp, 1);
		red = red->next;
		i++;
	}
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
