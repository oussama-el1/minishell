/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:03:06 by yslami            #+#    #+#             */
/*   Updated: 2025/03/03 00:19:45 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(int n, int base)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

static int	ft_get_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_fill_str(char *str, int n, int len, int offset)
{
	while (len > offset)
	{
		str[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n, int type)
{
	char	*str;
	int		len;
	int		offset;

	len = ft_get_len(n);
	str = (char *)maroc((len + 1) * sizeof(char), ALLOC, type);
	offset = 0;
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		offset = 2;
		n = 147483648;
	}
	if (n < 0)
	{
		str[0] = '-';
		offset = 1;
		n *= -1;
	}
	ft_fill_str(str, n, len, offset);
	str[len] = '\0';
	return (str);
}
