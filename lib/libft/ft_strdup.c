/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:06:20 by yslami            #+#    #+#             */
/*   Updated: 2025/03/02 23:38:22 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, int type)
{
	char	*str;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	str = (char *)maroc((s_len + 1) * sizeof(char), ALLOC, type);
	i = 0;
	while (i < s_len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
