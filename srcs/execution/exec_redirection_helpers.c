/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:24:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/14 02:52:33 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_ambiguous(char **expanded, int empty_flag)
{
	int	size;

	size = 0;
	while (expanded[size])
		size++;
	if (size > 1 || (!empty_flag && !*expanded[0]))
		return (1);
	return (0);
}

static void	handle_sigint_herdc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

void	herdoc_loop(const char *delimiter, int fd, t_helper *hp)
{
	char	*line;
	char	*tmp;

	line = NULL;
	signal(SIGINT, handle_sigint_herdc);
	while (1)
	{
		line = readline("> ");
		tmp = line;
		if (!line)
			return (herdoc_msg(delimiter, hp));
		if (g_exit_status == 130)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			return (free(tmp), (void)0);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(tmp);
	}
}

char	*handle_heredoc(const char *delimiter, t_helper *hp, int skip)
{
	static int	id;
	int			fd;
	char		*filename;

	if (!skip)
	{
		filename = ft_strjoin("/tmp/heredoc_", ft_itoa(++id, CMD), CMD);
		fd = fdmaroc(filename, HEREDOC, OPEN, O_WRONLY | O_CREAT | O_TRUNC);
		if (fd < 0)
			return (perror("open failed\n"), NULL);
		herdoc_loop(delimiter, fd, hp);
		return (filename);
	}
	else
		herdoc_loop(delimiter, -1, hp);
	return (NULL);
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
				fd = fdmaroc(redirection->filename, REDIR_OUT,
						OPEN, O_WRONLY | O_CREAT | O_TRUNC);
			else
				fd = fdmaroc(redirection->filename, REDIR_OUT,
						OPEN, O_WRONLY | O_CREAT | O_APPEND);
			if (fd < 0)
			{
				file_error_handler(redirection, error_found, 0, NULL);
				break ;
			}
		}
		i++;
		redirection = redirection->next;
	}
}
