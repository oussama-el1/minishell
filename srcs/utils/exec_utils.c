/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:28:39 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/15 07:55:09 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	clean_resources(t_helper *hp, int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	if (hp->node->args->herdoc_file)
		unlink(hp->node->args->herdoc_file);
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
