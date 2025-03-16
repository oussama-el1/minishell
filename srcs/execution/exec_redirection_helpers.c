/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:24:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/16 05:20:52 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint_herdc(int sig)
{
	if (sig == SIGINT)
	{
		// ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0); // Clear the current input
		// rl_on_new_line();
		// rl_redisplay();
		rl_done = 1;
		g_signals.sigint_heredoc = 1;
	}
}

void	herdoc_loop(const char *delimiter, int fd, t_helper *hp)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while (1)
	{
		if (g_signals.sigint_heredoc)
		{
			g_exit_status = 130;
			// signals.sigint_heredoc = 0;
			break ;
		}
		line = readline("> ");
		tmp = line;
		if (!line)
			return (herdoc_msg(delimiter, hp));
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
	char		*filename = NULL;

	signal(SIGINT, handle_sigint_herdc);
	if (!skip)
	{
		filename = ft_strjoin("/tmp/heredoc_", ft_itoa(++id, CMD), CMD);
		fd = fdmaroc(filename, HEREDOC, OPEN, O_WRONLY | O_CREAT | O_TRUNC);
		if (fd < 0)
			return (perror("open failed\n"), NULL);
		herdoc_loop(delimiter, fd, hp);
		signal(SIGINT, handle_sigint);
		return (filename);
	}
	else
		herdoc_loop(delimiter, -1, hp);
	signal(SIGINT, handle_sigint);
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
