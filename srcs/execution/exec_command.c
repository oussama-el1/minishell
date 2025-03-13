/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:04:38 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/13 20:28:26 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	enoent_handler(char *cmd)
{
	if (errno == ENOENT)
	{
		if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')
			|| (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": No such file or directory", 2);
			exit(127);
		}
	}
}

static void	error_handler(char *cmd)
{
	struct stat	buf;

	if (stat(cmd, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": is a directory", 2);
			exit(126);
		}
	}
	else
		enoent_handler(cmd);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	run_binary(char **argv, t_env *env)
{
	char	*cmd_path;

	cmd_path = get_executable_path(argv[0], env);
	if (!cmd_path)
		error_handler(argv[0]);
	execve(cmd_path, argv, get_env_array(env));
	perror(argv[0]);
	exit(1);
}

int	exec_binary(char **argv, t_env *env)
{
	pid_t	pid;
	int		status;

	if (!argv)
		return (1);
	pid = fork();
	if (pid == 0)
		run_binary(argv, env);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	ft_putendl_fd("unable to fork child process", 2);
	return (1);
}

int	exec_command(t_tree *cmd, t_helper *hp)
{
	char		**argv;
	t_expand	**expand;
	int			i;

	argv = cmd->args->argv;
	expand = cmd->args->expand_list;
	if (!*argv[0])
	{
		i = 0;
		while (argv[i] && !*argv[i] && expand[i] && expand[i]->type == DOLLAR)
			i++;
		if (argv[i] && !*argv[i])
		{
			ft_putstr_fd("minishell: : command not found\n", 2);
			return (127);
		}
		argv = &argv[i];
		cmd->args->argv = argv;
	}
	if (!argv[0])
		return (0);
	if (is_builtin(argv[0]))
		return (exec_builtin(argv, cmd->args->argv_cpy, hp));
	return (exec_binary(argv, *hp->env));
}
