/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:13:22 by yslami            #+#    #+#             */
/*   Updated: 2025/03/02 23:55:21 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_allocate(char **strings, char const *s, char sep, int type)
{
	char		**strings1;
	char const	*temp;

	strings1 = strings;
	temp = s;
	while (*s)
	{
		while (*s && *s == sep)
			++s;
		temp = s;
		while (*temp && *temp != sep)
			++temp;
		if (*temp == sep || temp > s)
		{
			*strings1 = ft_substr(s, 0, temp - s, type);
			s = temp;
			++strings1;
		}
	}
	*strings1 = NULL;
	return (1);
}

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
		{
			i++;
		}
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
		{
			i++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c, int type)
{
	char	**strings;
	int		count;

	if (!s || !*s)
		return (NULL);
	count = ft_count_words(s, c);
	strings = (char **)maroc((count + 1) * sizeof(char *), \
		ALLOC, type);
	ft_allocate(strings, s, c, type);
	return (strings);
}
