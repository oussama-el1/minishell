/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:13:22 by yslami            #+#    #+#             */
/*   Updated: 2025/03/16 03:21:03 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_allocate(char **strings, char const *s, char *delims, int type)
{
	char		**strings1;
	char const	*temp;

	strings1 = strings;
	while (*s)
	{
		while (*s && ft_strchr(delims, *s))
			++s;
		temp = s;
		while (*temp && !ft_strchr(delims, *temp))
			++temp;
		if (temp > s)
		{
			*strings1 = ft_substr(s, 0, temp - s, type);
			s = temp;
			++strings1;
		}
	}
	*strings1 = NULL;
	return (1);
}

static int	ft_count_words(char const *s, char *delims)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_strchr(delims, s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !ft_strchr(delims, s[i]))
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char *delims, int type)
{
	char	**strings;
	int		count;

	if (!s || !*s || !delims)
		return (NULL);
	count = ft_count_words(s, delims);
	strings = (char **)maroc((count + 1) * sizeof(char *), \
		ALLOC, type);
	ft_allocate(strings, s, delims, type);
	return (strings);
}
