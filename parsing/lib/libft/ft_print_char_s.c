/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:38:21 by yslami            #+#    #+#             */
/*   Updated: 2025/02/02 16:18:43 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_c_prc(va_list list, t_format p)
{
	int		count;
	char	c;

	count = 0;
	if (p.specifier == 'c')
		c = va_arg(list, int);
	else
		c = '%';
	p.precision = 1;
	if (!p.minus && p.zero)
		count += ft_putnchar_fd('0', 1, p.width - p.precision);
	else if (!p.minus && p.width > p.precision)
		count += ft_putnchar_fd(' ', 1, p.width - p.precision);
	count += ft_putchar_fd(c, 1);
	if (p.minus && p.width > p.precision)
		count += ft_putnchar_fd(' ', 1, p.width - p.precision);
	return (count);
}

int	ft_print_s(va_list list, t_format p)
{
	char	*str;
	int		count;

	str = va_arg(list, char *);
	if (!str)
		str = "(null)";
	count = 0;
	count += ft_putnchar_fd(' ', 1, -p.precision * p.neg_prec);
	if (count)
		return (count);
	if (!p.dot || p.precision > (int)ft_strlen(str))
		p.precision = ft_strlen(str);
	if (p.zero && p.width > p.precision)
		count += ft_putnchar_fd('0', 1, p.width - p.precision);
	else if (!p.minus && p.width > p.precision)
		count += ft_putnchar_fd(' ', 1, p.width - p.precision);
	count += ft_putstrn_fd(str, 1, p.precision);
	if (p.minus && p.width > p.precision)
		count += ft_putnchar_fd(' ', 1, p.width - p.precision);
	return (count);
}
