/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:24:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/09 04:04:19 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_ambiguous(char **expanded, int empty_flag)
{
	int	size;

	size = 0;
	while (expanded[size])
		size++;
	printf("empty flag : %d\n", empty_flag);
	if (size > 1 || (!empty_flag && !*expanded[0]))
	{
		printf("is ambigous\n");
		return (1);
	}
	printf("not ambigous\n");
	return (0);
}

void	herdoc_loop(const char *delimiter, int fd, t_helper *hp)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		tmp = line;
		if (!line)
			return (herdoc_msg(delimiter));
		expand_string(&line, *hp->env, hp->exit_status, 1);
		if (ft_strcmp(line, delimiter) == 0)
			return (free(tmp), (void)0);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(tmp);
	}
}

void	handle_heredoc(const char *delimiter, t_helper *hp)
{
	int	fd;

	signal(SIGINT, SIG_DFL);
	fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open failed\n"));
	herdoc_loop(delimiter, fd, hp);
	close(fd);
}

void	file_error_handler(t_redir *redirection, int *error_found,
		int ambiguous, t_ambiguous_err *err)
{
	if (!ambiguous)
	{
		ft_putstr_fd("minishell: ", 2);
		if (!*redirection->filename)
		{
			ft_putstr_fd(redirection->filename, 2);
			ft_putstr_fd(":", 2);
		}
		perror(redirection->filename);
	}
	else
		ambiguous_redirect(err->filename);
	*error_found = 1;
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
