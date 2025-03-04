/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:04:38 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/04 20:57:39 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **argv, t_env *env, int exit_status)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv, env, exit_status));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(env, exit_status));
	if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, env, exit_status));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv, env));
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(argv, env));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argv));
	return (0);
}

static void	error_handler(char *cmd)
{
	struct stat	buf;

	// Check if the file exists
	if (stat(cmd, &buf) == 0)
	{
		// Check if it's a directory
		if (S_ISDIR(buf.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": is a directory", 2);
			exit(126);
		}
		// Check if it's not executable
		else if (access(cmd, X_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": Permission denied", 2);
			exit(126);
		}
	}
	else
	{
		// Ensure stat() failure is due to file not existing
		if (errno == ENOENT)
		{
			// If the command starts with '/', './', or '../', it's expected to be a path
			if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') ||
				(cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putendl_fd(": No such file or directory", 2);
				exit(127);
			}
		}
	}

	// If none of the above conditions matched, it's an unknown command
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	run_binary(char **argv, t_env *env, int exit_status)
{
	char	*cmd_path;

	cmd_path = get_executable_path(argv[0], env, exit_status);
	if (!cmd_path)
		error_handler(argv[0]);
	execve(cmd_path, argv, get_env_array(env));
	perror(argv[0]);
	exit(1);
}

int	exec_binary(char **argv, t_env *env, int exit_status)
{
	pid_t	pid;
	int		status;

	if (!argv)
		return (1);
	pid = fork();
	if (pid == 0)
		run_binary(argv, env, exit_status);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	ft_putendl_fd("unable to fork child process", 2);
	return (1);
}

int	exec_command(t_tree *cmd, t_env *env, int exit_status)
{
	char **argv;
	int	i;

	argv = cmd->args->argv;
	if (!*argv[0])
	{
		i = 0;
		while (argv[i] && !*argv[i])
			i++;
		argv = &argv[i];
		cmd->args->argv = argv;
	}
	if (!argv[0])
		return (0);
	if (is_builtin(argv[0]))
		return (exec_builtin(argv, env, exit_status));
	return (exec_binary(argv, env, exit_status));
}
