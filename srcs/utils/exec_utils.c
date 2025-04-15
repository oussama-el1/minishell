/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:28:39 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/16 23:48:15 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *str)
{
	int		i;
	char	*key;

	if (!str || !str[0])
		return (NULL);
	if (str[0] == '?')
		return (ft_strdup("?", CMD));
	i = 0;
	while (str[i] && (ft_is_alnum(str[i]) || str[i] == '_'))
		i++;
	key = ft_substr(str, 0, i, CMD);
	return (key);
}

void	execute_herdocs(t_helper *hp)
{
	t_tree	*parent;

	if (!hp->node)
		return ;
	if (hp->node->args && hp->node->type == T_CMD)
		herdoc_runner(hp->node->args->redir, hp);
	if (hp->node->type == T_SUBSHELL)
	{
		parent = hp->node;
		hp->node = parent->left;
		execute_herdocs(hp);
		hp->node = parent;
		if (hp->node->args)
			herdoc_runner(hp->node->args->redir, hp);
	}
	if (hp->node->type == T_PIPE
		|| hp->node->type == T_AND || hp->node->type == T_OR)
	{
		parent = hp->node;
		hp->node = parent->left;
		execute_herdocs(hp);
		hp->node = parent->right;
		execute_herdocs(hp);
		hp->node = parent;
	}
}

int	count_matching_files(const char *pattern, int *count)
{
	DIR				*dir;
	struct dirent	*entry;

	*count = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && matches_pattern(entry->d_name, pattern))
			(*count)++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (1);
}

void	clean_resources(int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

int	check_expanded(t_redir *redir)
{
	t_expand	*curr;

	curr = redir->expand_list;
	while (curr)
	{
		if (curr->type == S_Q || curr->type == D_Q)
			return (0);
		curr = curr->next;
	}
	return (1);
}
