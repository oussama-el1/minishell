/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:10:12 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/09 03:29:06 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (errno == ENOENT)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (errno == ENOTDIR)
		ft_putstr_fd(": Not a directory\n", 2);
	else if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", 2);
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}

void	process_herdocs(t_helper *hp, t_herdoc *herdoc, int left)
{
	herdoc->last_herdoc = NULL;
	if (hp->node->left->args && left)
		herdoc->index = get_last_heredoc(hp->node->left->args->redir,
				&herdoc->last_herdoc, hp);
	else if (hp->node->right->args && !left)
		herdoc->index = get_last_heredoc(hp->node->right->args->redir,
				&herdoc->last_herdoc, hp);
}

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
