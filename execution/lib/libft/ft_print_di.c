/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_di.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:20:32 by yslami            #+#    #+#             */
/*   Updated: 2025/02/02 16:11:20 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_int(char *num_str, t_format p);
static int	ft_print_sign_precision(t_format p);
static int	ft_print_i(char *num_str, t_format p);
static	int	ft_handle_zero_precision(t_format p);

int	ft_print_di(int nbr, t_format p)
{
	char	*num_str;
	int		count;

	count = 0;
	if (nbr < 0)
		p.neg = 1;
	if (p.precision == 0 && nbr == 0)
		return (ft_handle_zero_precision(p));
	num_str = ft_itoa(nbr);
	if (!num_str)
		return (0);
	count += ft_print_int(num_str, p);
	free(num_str);
	return (count);
}

static int	ft_print_int(char *num_str, t_format p)
{
	int	count;

	count = 0;
	if (p.precision >= 0 && p.zero)
		p.zero = 0;
	if ((p.plus || p.space) && !p.neg)
		--p.width;
	if (p.precision == 0 || p.precision < (int)ft_strlen(num_str))
		p.precision = -1;
	if (p.zero)
		count += ft_print_sign_precision(p);
	if (p.minus)
		count += ft_print_i(num_str, p);
	if (p.precision >= 0)
	{
		p.width -= p.precision;
		count += ft_putnchar_fd(' ', 1, p.width - p.neg);
	}
	else
		count += ft_putnchar_fd(ft_type(p), 1, p.width - ft_strlen(num_str));
	if (!p.minus)
		count += ft_print_i(num_str, p);
	return (count);
}

static int	ft_print_sign_precision(t_format p)
{
	int	count;

	count = 0;
	if (p.neg)
		count += ft_putchar_fd('-', 1);
	else if (p.plus && !p.neg)
		count += ft_putchar_fd('+', 1);
	else if (p.space)
		count += ft_putchar_fd(' ', 1);
	return (count);
}

static int	ft_print_i(char *num_str, t_format p)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(num_str);
	if (p.plus && !p.zero && !p.neg)
		count += ft_putchar_fd('+', 1);
	else if (p.space && !p.zero && !p.neg)
		count += ft_putchar_fd(' ', 1);
	if (p.neg && !p.zero)
		count += ft_putchar_fd('-', 1);
	if (p.neg)
		len--;
	if (p.precision >= 0)
		count += ft_putnchar_fd('0', 1, p.precision - len);
	if (p.neg)
		return (count += ft_putstrn_fd(num_str + 1, 1, len));
	return (count += ft_putstrn_fd(num_str, 1, len));
}

static	int	ft_handle_zero_precision(t_format p)
{
	int	count;

	count = 0;
	if (p.plus)
		p.width--;
	if (p.minus && p.plus)
		count += ft_putchar_fd('+', 1);
	if (p.space && !p.width)
		count += ft_putchar_fd(' ', 1);
	count += ft_putnchar_fd(' ', 1, p.width);
	if (!p.minus && p.plus)
		count += ft_putchar_fd('+', 1);
	return (count);
}
