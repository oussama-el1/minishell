/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:27:10 by yslami            #+#    #+#             */
/*   Updated: 2025/03/03 00:33:47 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, int type)
{
	char	*result;
	int		len1;
	int		len2;

	if (!s1 && !s2)
		return (ft_strdup("", type));
	if (s1 && !s2)
		return (ft_strdup(s1, type));
	if (!s1 && s2)
		return (ft_strdup(s2, type));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)maroc((len1 + len2 + 1) * sizeof(char), ALLOC, type);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	return (result);
}
