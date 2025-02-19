/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:25:48 by yslami            #+#    #+#             */
/*   Updated: 2025/02/02 16:25:05 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_sharp(t_format p)
{
	if (p.specifier == 'X')
		return ("0X");
	return ("0x");
}

static int	ft_recursive_hex(t_format p, size_t n, size_t iter)
{
	int		count;
	int		remainder;
	char	character;

	count = 0;
	if (n > 0 || (!iter && (p.specifier != 'p' || !p.dot)))
	{
		remainder = n % 16;
		if (p.specifier == 'X')
			character = HEXAUP[remainder];
		else
			character = HEXALOW[remainder];
		n /= 16;
		iter = 1;
		count += ft_recursive_hex(p, n, iter);
		count += ft_putchar_fd(character, 1);
	}
	return (count);
}

static void	ft_handle_printing(t_format p, int n, int *count, int len)
{
	if (p.sharp && n && p.zero && !p.dot)
	{
		*count += ft_putstrn_fd(ft_sharp(p), 1, 2);
		if (p.width > len)
			*count += ft_putnchar_fd('0', 1, p.width - len);
	}
	else
	{
		if (!p.minus)
		{
			if (p.zero && !p.dot)
				*count += ft_putnchar_fd('0', 1, p.width - p.precision);
			else
				*count += ft_putnchar_fd(' ', 1, p.width - p.precision);
		}
		if (p.sharp && n)
			*count += ft_putstrn_fd(ft_sharp(p), 1, 2);
	}
	*count += ft_putnchar_fd('0', 1, (p.precision - len));
}

int	ft_print_hex(unsigned int n, t_format p)
{
	int	count;
	int	len;

	count = 0;
	len = ft_nbrlen(n, 16);
	if (!n && !p.precision && p.dot)
		len = 0;
	if (p.precision < 0 || p.precision < len || !p.dot)
		p.precision = len;
	if (p.sharp && n)
		p.width -= 2;
	ft_handle_printing(p, n, &count, len);
	if (len)
		count += ft_recursive_hex(p, n, n);
	if (p.minus && p.width > p.precision)
		count += ft_putnchar_fd(' ', 1, p.width - p.precision);
	return (count);
}

int	ft_print_p(void *ptr, t_format p)
{
	uintptr_t	n;
	int			count;
	int			len;

	n = (uintptr_t)ptr;
	count = 0;
	len = ft_nbrlen(n, 16);
	len *= !(!n && !p.precision && p.dot);
	if (p.precision < len || !p.dot)
		p.precision = len;
	count += ft_putstrn_fd("0x", 1, 2 * p.zero);
	p.width -= 2;
	if (!p.minus && p.width > p.precision && !p.dot && p.zero)
		count += ft_putnchar_fd('0', 1, (p.width - p.precision));
	else if (!p.minus && p.width > p.precision)
		count += ft_putnchar_fd(' ', 1, p.width - p.precision);
	count += ft_putstrn_fd("0x", 1, 2 * !p.zero);
	count += ft_putnchar_fd('0', 1, (p.precision - len) * (n != 0));
	count += ft_putnchar_fd('0', 1, p.precision * (p.dot && !n));
	if (len)
		count += ft_recursive_hex(p, n, n);
	if (p.minus && p.width > p.precision)
		count += ft_putnchar_fd(' ', 1, p.width - p.precision);
	return (count);
}
