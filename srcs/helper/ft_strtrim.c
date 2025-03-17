/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:14:02 by yslami            #+#    #+#             */
/*   Updated: 2025/03/17 06:31:10 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrim(char const *s1, char const *set, int type)
{
	char	*trimmed;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1, type));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		++start;
	if (start > 1)
		return (ft_strdup("", CMD));
	while (end >= 0 && s1[end] && ft_strrchr(set, s1[end]))
		--end;
	trimmed = ft_substr(s1, start, end - start + 1, type);
	return (trimmed);
}
