/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:38:07 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/10 04:06:28 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_heredoc(const char *delimiter, t_env *env)
{
	int		fd;
	char	*line = NULL;
	char	*var_value = NULL;

	signal(SIGINT, SIG_DFL);
	fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open failed");
		return;
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (line[0] == '$')
		{
			var_value = get_env_var(env, &line[1]);
			printf("get value : %s  -> (%zu)\n", var_value, ft_strlen(var_value));
			if (var_value)
				write(fd, var_value, ft_strlen(var_value));
		}
		else
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}

	close(fd);
	fd = open("/tmp/heredoc_tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("open failed");
		return;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		return;
	}
	close(fd);
	unlink("/tmp/heredoc_tmp");
}

int	exec_redirection(t_tree *node, t_env *env)
{
	int fd;
	int res = 0;
	int saved_stdin = -1;
	int	saved_stdout = -1;

	if (!node || (!node->filename && node->heredoc_delim))
	{
		ft_putendl_fd("Redirection error: Missing filename", 2);
		return (1);
	}

	if (node->type == REDIR_IN)
	{
		saved_stdin = dup(STDIN_FILENO);
		fd = open(node->filename, O_RDONLY);
		if (fd < 0)
		{
			perror(node->filename);
			return (1);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2 failed");
			close(fd);
			return (1);
		}
		close(fd);
	}
	else if (node->type == REDIR_OUT || node->type == REDIR_APPEND)
	{
		saved_stdout = dup(STDOUT_FILENO);
		fd = open(node->filename, O_WRONLY | O_CREAT |
				(node->type == REDIR_OUT ? O_TRUNC : O_APPEND), 0644);
		if (fd < 0)
		{
			perror(node->filename);
			return (1);
		}
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 failed");
			close(fd);
			return (1);
		}
		close(fd);
	}
	else if (node->type == HEREDOC)
		handle_heredoc(node->heredoc_delim, env);

	if (node->left)
		res = execute_ast(node->left, env);
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}

	return res;
}
