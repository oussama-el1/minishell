/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:36:17 by yslami            #+#    #+#             */
/*   Updated: 2025/03/03 00:33:10 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, int type)
{
	char	*substr;
	size_t	size;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup("", type));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	substr = (char *)maroc((len + 1) * sizeof(char), ALLOC, type);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
