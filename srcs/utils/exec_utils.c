/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:28:39 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/13 02:48:57 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_splited(t_expand *expand)
{
	while (expand)
	{
		if (expand->type != DOLLAR && expand->type != EXPR)
			return (0);
		expand = expand->next;
	}
	return (1);
}

char	**split_arg(char *new_arg, t_expand *cp, t_helper *hp)
{
	char	**splitted;

	hp->splited = is_splited(cp);
	if (ft_strchr(new_arg, ' ') && !hp->export && hp->splited)
		return (ft_split(new_arg, ' ', CMD));
	splitted = maroc(sizeof(char *) * 2, ALLOC, CMD);
	splitted[0] = new_arg;
	splitted[1] = NULL;
	return (splitted);
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

void	clean_resources(t_helper *hp, int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	if (hp->node->args->herdoc_file)
		unlink(hp->node->args->herdoc_file);
}
