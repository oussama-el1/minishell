/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:24:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/05 23:14:23 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env_herdoc(t_env *env, char *line, int fd, int exit_status, const char *delimiter)
{
	char	*var_value;

	var_value = get_env_var(env, &line[1], exit_status);
	if (var_value && ft_strcmp(var_value, delimiter))
	{
		write(fd, var_value, ft_strlen(var_value));
		return (var_value);
	}
	return (NULL);
}

void	herdoc_loop(const char *delimiter, t_env *env, int fd, int exit_status)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		tmp = line;
		if (!line)
			break ;
		expand_string(&line, env, exit_status, 1);
		if (ft_strcmp(line, delimiter) == 0)
			return (free(tmp), (void)0);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(tmp);
	}
}

void	handle_heredoc(const char *delimiter, t_env *env, int exit_status)
{
	int	fd;

	signal(SIGINT, SIG_DFL);
	fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open failed");
		return ;
	}
	herdoc_loop(delimiter, env, fd, exit_status);
	close(fd);
}

int	get_last_heredoc(t_redir *redirection, t_redir **last_heredoc,
	int exit_status, t_env *env)
{
	int	i;
	int	last_heredoc_index;

	i = 0;
	last_heredoc_index = -1;
	*last_heredoc = NULL;
	while (redirection)
	{
		if (redirection->type == R_HEREDOC)
		{
			handle_heredoc(redirection->heredoc_delim, env, exit_status);
			*last_heredoc = redirection;
			last_heredoc_index = i;
		}
		redirection = redirection->next;
		i++;
	}
	return (last_heredoc_index);
}

void	file_error_handler(t_redir *redirection, int *error_found, int ambiguous)
{
	if (!ambiguous)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirection->filename, 2);
		ft_putstr_fd(":", 2);
		perror(redirection->filename);
	}
	*error_found = 1;
}
