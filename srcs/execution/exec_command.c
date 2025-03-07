/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:04:38 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/05 22:34:29 by oel-hadr         ###   ########.fr       */
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

int	exec_builtin(char **argv, char **arg_cpy, t_env **env, int exit_status)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv, arg_cpy));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv, *env, exit_status));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(*env, exit_status));
	if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, *env, exit_status));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv, env));
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(argv, *env));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argv));
	return (0);
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
	{
		if (errno == ENOENT)
		{
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

int	exec_command(t_tree *cmd, t_env **env, int exit_status)
{
	char		**argv;
	t_expand	**expand;
	int	i;

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
		return (exec_builtin(argv, cmd->args->argv_cpy, env, exit_status));
	return (exec_binary(argv, *env, exit_status));
}
