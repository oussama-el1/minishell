/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:07:32 by yslami            #+#    #+#             */
/*   Updated: 2024/12/14 20:20:53 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	c = (unsigned char)c;
	while (*ptr)
	{
		if (*ptr == c)
		{
			return (ptr);
		}
		ptr++;
	}
	if (c == 0)
		return (ptr);
	return (NULL);
}
