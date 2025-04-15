/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:34:27 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/15 21:16:43 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_matching_files(const char *pattern, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				i;

	if (!count_matching_files(pattern, count) || !(*count))
		return (NULL);
	files = maroc((*count + 1) * sizeof(char *), ALLOC, CMD);
	dir = opendir(".");
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && matches_pattern(entry->d_name, pattern))
			files[i++] = ft_strdup(entry->d_name, CMD);
		entry = readdir(dir);
	}
	files[i] = NULL;
	closedir(dir);
	return (files);
}

static void	set_files(char **new_argv, char **files, int file_count, int *k)
{
	int	j;

	j = 0;
	while (j < file_count)
	{
		new_argv[*k] = files[j];
		*k += 1;
		j += 1;
	}
}

static void	fill_new_argv(char **new_argv, char **old_argv, bool *wildcards)
{
	int		i;
	int		k;
	int		file_count;
	char	**files;

	i = 0;
	k = 0;
	while (old_argv[i])
	{
		if (wildcards[i])
		{
			files = get_matching_files(old_argv[i], &file_count);
			if (files)
				set_files(new_argv, files, file_count, &k);
			else
				new_argv[k++] = ft_strdup(old_argv[i], CMD);
		}
		else
			new_argv[k++] = ft_strdup(old_argv[i], CMD);
		i++;
	}
	new_argv[k] = NULL;
}

static int	count_wildcard(char **old_argv, bool *wildcards)
{
	int		i;
	int		count;
	int		file_count;
	char	**files;

	i = 0;
	count = 0;
	while (old_argv[i])
	{
		if (wildcards[i])
		{
			files = get_matching_files(old_argv[i], &file_count);
			if (files)
				count += file_count;
			else
				count += 1;
		}
		else
			count++;
		i++;
	}
	return (count);
}

void	expand_wildcard(t_helper *hp)
{
	char	**old_argv;
	char	**new_argv;
	int		count;

	old_argv = hp->node->args->argv;
	count = count_wildcard(old_argv, hp->node->args->wildcards);
	new_argv = maroc((count + 1) * sizeof(char *), ALLOC, CMD);
	if (!new_argv)
		return ;
	fill_new_argv(new_argv, old_argv, hp->node->args->wildcards);
	hp->node->args->argv = new_argv;
}
