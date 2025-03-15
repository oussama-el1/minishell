/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:24:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/15 05:12:19 by yslami           ###   ########.fr       */
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
		// ioctl(STDIN_FILENO, TIOCSTI, "\n");
		// write(STDOUT_FILENO, "\n", 1);
		exit(g_exit_status);
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
			return (herdoc_msg(delimiter, hp), exit(0));
		if (ft_strcmp(line, delimiter) == 0)
			return (free(tmp), (void)0, exit(0));
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(tmp);
	}
}

char	*handle_heredoc(const char *delimiter, t_helper *hp, int skip)
{
	static int	id;
	int			fd;
	int			pipefd[2];
	char		*filename = NULL;
	pid_t		pid;

	if (pipe(pipefd) == -1) {
		perror("pipe failed");
		return (NULL);
	}
	pid = fork();
	hp->herdoc_sigint = 0;
	if (pid == 0)
	{
		close(pipefd[0]);
		if (!skip)
		{
			filename = ft_strjoin("/tmp/heredoc_", ft_itoa(++id, CMD), CMD);
			fd = fdmaroc(filename, HEREDOC, OPEN, O_WRONLY | O_CREAT | O_TRUNC);
			if (fd < 0)
				exit(1);

			// Send filename to parent
			write(pipefd[1], filename, strlen(filename) + 1);
			close(pipefd[1]);

			herdoc_loop(delimiter, fd, hp);
		}
		else
		{
			herdoc_loop(delimiter, -1, hp);
			close(pipefd[1]);
		}
		exit(0);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		waitpid(-1, &g_exit_status, 0);
		if (WEXITSTATUS(g_exit_status) == 130)
		{
			g_exit_status = WEXITSTATUS(g_exit_status);
			
			hp->herdoc_sigint = 1;	
		}
		filename = maroc(256, ALLOC, CMD);
		if (read(pipefd[0], filename, 256) > 0)
			return (close(pipefd[0]), filename);
		else
			return (close(pipefd[0]), NULL);
	}
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
