/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:04:38 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/06 05:20:44 by oel-hadr         ###   ########.fr       */
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

int	exec_builtin(t_tree *cmd, t_env *env)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_cd(cmd->argv, env));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(env));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(cmd->argv, env));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(cmd->argv, env));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(cmd->argv, env));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (ft_exit(cmd->argv));
	return (0);
}

int exec_binary(char **argv, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	pid = fork();
	if (pid == 0)
	{
		cmd_path = get_executable_path(argv[0], env);	
		if (!cmd_path)
		{
			ft_printf("minishell: %s: command not found\n", argv[0], 2);
			exit(127);
		}
		execve(cmd_path, argv, get_env_array(env));
		perror(argv[0]);
		free(cmd_path);
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return WEXITSTATUS(status);
	}
	else
	{
		ft_putendl_fd("unable to fork child process", 2);
		return (1);
	}
}

int	exec_command(t_tree *cmd, t_env *env)
{
	if (is_builtin(cmd->argv[0]))
		return (exec_builtin(cmd, env));
	return (exec_binary(cmd->argv, env));
}
