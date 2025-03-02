/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:34:27 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/02 02:03:41 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	contain_wildcard(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "*") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	count_files_in_Dir(int *count)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
	{
		*count = 0;
		return (0);
	}
	*count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
			(*count)++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (1);
}

char	**set_files(DIR *dir, int count)
{
	struct dirent	*entry;
	int				i;
	char			**files;

	files = malloc((count + 1) * sizeof(char *));
	if (!files)
		return (NULL);
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
		{
			files[i] = ft_strdup(entry->d_name);
			i++;
		}
		entry = readdir(dir);
	}
	files[i] = NULL;
	return (files);
}

char	**get_files_in_directory(int *count)
{
	DIR		*dir;
	char	**files;

	if (!count_files_in_Dir(count) || *count == 0)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	files = set_files(dir, *count);
	closedir(dir);
	return (files);
}

int	count_wildcard(char **old_argv)
{
	int	i;
	int	count;
	int	file_count;

	i = 0;
	count = 0;
	while (old_argv[i])
	{
		if (ft_strcmp(old_argv[i], "*") == 0)
		{
			get_files_in_directory(&file_count);
			count += file_count;
		}
		else
			count++;
		i++;
	}
	return (count);
}

void	fill_new_argv(char **new_argv, char **old_argv)
{
	int		i;
	int		j;
	int		k;
	int		file_count;
	char	**files;

	i = 0;
	k = 0;
	while (old_argv[i])
	{
		if (ft_strcmp(old_argv[i], "*") == 0)
		{
			files = get_files_in_directory(&file_count);
			j = 0;
			while (j < file_count)
				new_argv[k++] = files[j++];
			free(files);
		}
		else
			new_argv[k++] = ft_strdup(old_argv[i]);
		i++;
	}
	new_argv[k] = NULL;
}

void	expand_wildcard(char ***argv)
{
	char	**old_argv;
	char	**new_argv;
	int		count;

	old_argv = *argv;
	count = count_wildcard(old_argv);
	new_argv = malloc((count + 1) * sizeof(char *));
	if (!new_argv)
		return ;
	fill_new_argv(new_argv, old_argv);
	free(old_argv);
	*argv = new_argv;
}
