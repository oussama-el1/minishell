/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:27:10 by yslami            #+#    #+#             */
/*   Updated: 2024/12/14 20:21:23 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		len1;
	int		len2;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	return (result);
}
