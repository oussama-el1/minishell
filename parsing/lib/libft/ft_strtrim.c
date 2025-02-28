/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:14:02 by yslami            #+#    #+#             */
/*   Updated: 2024/12/14 20:22:44 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
	{
		return (ft_strdup(s1));
	}
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
	{
		++start;
	}
	while (s1[end] && ft_strrchr(set, s1[end]))
	{
		--end;
	}
	trimmed = ft_substr(s1, start, end - start + 1);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
