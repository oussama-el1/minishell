/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:09:12 by yslami            #+#    #+#             */
/*   Updated: 2024/12/09 12:58:07 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_buffer(int fd, char **stash, char *buffer)
{
	char	*tmp;
	int		bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
	{
		free(*stash);
		*stash = NULL;
		return (-1);
	}
	if (bytes == 0)
		return (bytes);
	buffer[bytes] = '\0';
	tmp = ft_strjoin_0(*stash, buffer);
	if (!tmp)
	{
		free(*stash);
		*stash = NULL;
		return (-1);
	}
	free(*stash);
	*stash = tmp;
	return (bytes);
}

static void	get_result(char **stash, char **result)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	tmp = ft_strchr_0(*stash, '\n');
	if (!tmp)
		len = ft_strlen_0(*stash);
	else
		len = ft_strlen_0(*stash) - ft_strlen_0(tmp) + 1;
	*result = (char *)malloc((len + 1) * sizeof(char));
	if (!*result)
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
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

	nl = ft_strchr_0(*stash, '\n');
	if (!nl)
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
	tmp = ft_strdup_0(++nl);
	if (!tmp)
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
	free(*stash);
	*stash = tmp;
	if (**stash == 0)
	{
		free(*stash);
		*stash = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*result;
	char		*buffer;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((size_t)BUFFER_SIZE == SIZE_MAX)
		return (NULL);
	buffer = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	bytes = 1;
	while (ft_strchr_0(stash, '\n') == NULL && bytes > 0)
		bytes = read_buffer(fd, &stash, buffer);
	free(buffer);
	if (bytes == -1 || (stash && ft_strlen_0(stash)) == 0)
		return (NULL);
	get_result(&stash, &result);
	clear_stash(&stash);
	return (result);
}
