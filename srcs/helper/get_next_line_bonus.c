/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:40:55 by yslami            #+#    #+#             */
/*   Updated: 2025/03/11 17:56:31 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	read_buffer(int fd, char **stash, char *buffer)
{
	int		bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
	{
		*stash = NULL;
		return (-1);
	}
	if (bytes == 0)
		return (bytes);
	buffer[bytes] = '\0';
	*stash = ft_strjoin(*stash, buffer, CMD);
	return (bytes);
}

static void	get_result(char **stash, char **result)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	tmp = ft_strchr(*stash, '\n');
	if (!tmp)
		len = ft_strlen(*stash);
	else
		len = ft_strlen(*stash) - ft_strlen(tmp) + 1;
	*result = (char *)maroc((len + 1) * sizeof(char), ALLOC, CMD);
	i = 0;
	while (i < len)
	{
		(*result)[i] = (*stash)[i];
		i++;
	}
	(*result)[i] = '\0';
}

static void	clear_stash(char **stash)
{
	char	*nl;
	char	*tmp;

	nl = ft_strchr(*stash, '\n');
	if (!nl)
	{
		*stash = NULL;
		return ;
	}
	tmp = ft_strdup(++nl, CMD);
	*stash = tmp;
	if (**stash == 0)
		*stash = NULL;
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FILES_OPENED];
	char		*result;
	char		*buffer;
	int			bytes;

	printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
	printf("file descriptor: %d\n", fd);
	if (fd < 0 || fd >= MAX_FILES_OPENED || BUFFER_SIZE <= 0)
		return (NULL);
	if ((size_t)BUFFER_SIZE == SIZE_MAX)
		return (NULL);
	buffer = (char *)maroc(((size_t)BUFFER_SIZE + 1) * sizeof(char), \
			ALLOC, CMD);
	bytes = 1;
	printf("call get_next_line\n");
	while (ft_strchr(stash[fd], '\n') == NULL && bytes > 0)
		bytes = read_buffer(fd, &stash[fd], buffer);
	if (bytes == -1 || ft_strlen(stash[fd]) == 0)
		return (NULL);
	get_result(&stash[fd], &result);
	clear_stash(&stash[fd]);
	return (result);
}
