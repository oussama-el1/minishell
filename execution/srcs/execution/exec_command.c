/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:04:38 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/25 13:31:24 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char *cmd)
{
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

int	exec_builtin(t_tree *cmd, t_env *env, int exit_status)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_cd(cmd->argv, env, exit_status));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(env, exit_status));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(cmd->argv, env, exit_status));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(cmd->argv, env));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(cmd->argv, env));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (ft_exit(cmd->argv));
	return (0);
}

void	run_binary(char **argv, t_env *env, int exit_status)
{
	char	*cmd_path;

	cmd_path = get_executable_path(argv[0], env, exit_status);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(cmd_path, argv, get_env_array(env));
	perror(argv[0]);
	free(cmd_path);
	exit(1);
}

int	exec_binary(char **argv, t_env *env, int exit_status)
{
	pid_t	pid;
	int		status;

	if (!argv || !*argv[0])
		return (0);
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
	if (is_builtin(cmd->argv[0]))
		return (exec_builtin(cmd, env, exit_status));
	return (exec_binary(cmd->argv, env, exit_status));
}
