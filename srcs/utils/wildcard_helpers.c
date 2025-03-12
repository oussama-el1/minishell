/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:24:17 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/12 01:25:15 by oel-hadr         ###   ########.fr       */
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
