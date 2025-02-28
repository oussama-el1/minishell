/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:29:03 by yslami            #+#    #+#             */
/*   Updated: 2025/02/02 16:29:24 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_utoa_len(unsigned int nbr)
{
	unsigned int	len;

	if (nbr == 0)
		return (1);
	len = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_utoa(unsigned int nbr)
{
	char			*str;
	unsigned int	i;

	if (nbr == 0)
		return (ft_strdup("0"));
	i = ft_utoa_len(nbr);
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (nbr != 0)
	{
		str[--i] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}
