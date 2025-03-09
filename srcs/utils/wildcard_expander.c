/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:34:27 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/09 04:52:44 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contain_wildcard(char **argv, bool *wildcards)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (wildcards[i])
			return (1);
		i++;
	}
	return (0);
}

static int	match_recursive(const char *filename, const char *pattern)
{
	while (*pattern && *filename)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (1);
			while (*filename)
			{
				if (match_recursive(filename, pattern))
					return (1);
				filename++;
			}
			return (0);
		}
		else if (*pattern != *filename)
			return (0);
		filename++;
		pattern++;
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern && !*filename);
}

int	matches_pattern(const char *filename, const char *pattern)
{
	return (match_recursive(filename, pattern));
}

char	**get_matching_files(const char *pattern, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;

	*count = 0;
	if (!(dir = opendir(".")))
		return (NULL);
	while ((entry = readdir(dir)))
		if (entry->d_name[0] != '.' && matches_pattern(entry->d_name, pattern))
			(*count)++;
	closedir(dir);
	if (!(*count))
		return (NULL);
	files = maroc((*count + 1) * sizeof(char *), ALLOC, CMD);
	dir = opendir(".");
	int i = 0;
	while ((entry = readdir(dir)))
		if (entry->d_name[0] != '.' && matches_pattern(entry->d_name, pattern))
			files[i++] = ft_strdup(entry->d_name, CMD);
	files[i] = NULL;
	closedir(dir);
	return (files);
}

int	count_wildcard(char **old_argv, bool *wildcards)
{
	int	i;
	int	count;
	int	file_count;
	char **files;

	i = count = 0;
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

void	fill_new_argv(char **new_argv, char **old_argv, bool *wildcards)
{
	int		i, j, k, file_count;
	char	**files;

	i = k = 0;
	while (old_argv[i])
	{
		if (wildcards[i])
		{
			files = get_matching_files(old_argv[i], &file_count);
			if (files)
			{
				j = 0;
				while (j < file_count)
					new_argv[k++] = files[j++];
			}
			else
				new_argv[k++] = ft_strdup(old_argv[i], CMD);
		}
		else
			new_argv[k++] = ft_strdup(old_argv[i], CMD);
		i++;
	}
	new_argv[k] = NULL;
}

void	expand_wildcard(char ***argv, bool *wildcards)
{
	char	**old_argv;
	char	**new_argv;
	int		count;

	old_argv = *argv;
	count = count_wildcard(old_argv, wildcards);
	new_argv = maroc((count + 1) * sizeof(char *), ALLOC, CMD);
	if (!new_argv)
		return ;
	fill_new_argv(new_argv, old_argv, wildcards);
	*argv = new_argv;
}
