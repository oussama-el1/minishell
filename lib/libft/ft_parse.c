/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:24:48 by yslami            #+#    #+#             */
/*   Updated: 2025/02/02 16:05:57 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_parse_flag(const char *str, t_format *p, int i);
static void	ft_print_arg(char type, t_format *p, va_list list);
static void	ft_parse_width(const char *str, t_format *p, int i);
static void	ft_parse_precision(const char *str, t_format *p, int i);

void	ft_parse_bonus(const char *str, va_list list, t_format *p)
{
	int	i;
	int	speclen;

	i = -1;
	while (str[++i])
	{
		ft_reset_format(p);
		if (str[i] == '%')
		{
			speclen = ft_parse_flag(str, p, i);
			if (p->specifier)
				i = speclen;
			if (str[i] && (p->specifier > 0) && ft_isspecific(str[i]))
				ft_print_arg(str[i], p, list);
			else if (str[i] && str[i] != '%')
				p->len += ft_putchar_fd(str[i], 1);
		}
		else
			p->len += ft_putchar_fd(str[i], 1);
	}
}

static int	ft_parse_flag(const char *str, t_format *p, int i)
{
	while (str[++i] && ft_isflag(str[i]))
	{
		if (str[i] == '-' && !p->dot)
			ft_flags_minus(p);
		else if (str[i] == '#')
			p->sharp = 1;
		else if (str[i] == ' ')
			p->space = 1;
		else if (str[i] == '+')
			p->plus = 1;
		else if (str[i] == '0' && !p->minus && !p->width)
			p->zero = 1;
		if (ft_isdigit(str[i]) && !p->width && !p->dot)
			ft_parse_width(str, p, i);
		if (str[i] == '.')
			ft_parse_precision(str, p, i);
		if (ft_isspecific(str[i]))
		{
			p->specifier = str[i];
			break ;
		}
	}
	return (i);
}

static void	ft_print_arg(char type, t_format *p, va_list list)
{
	if (type == 'c' || type == '%')
		p->len += ft_print_c_prc(list, *p);
	else if (type == 's')
		p->len += ft_print_s(list, *p);
	else if (type == 'd' || type == 'i')
		p->len += ft_print_di(va_arg(list, int), *p);
	else if (type == 'u')
		p->len += ft_print_u(va_arg(list, unsigned int), *p);
	else if (type == 'x' || type == 'X')
		p->len += ft_print_hex(va_arg(list, unsigned int), *p);
	else if (type == 'p')
		p->len += ft_print_p(va_arg(list, void *), *p);
}

static void	ft_parse_width(const char *str, t_format *p, int i)
{
	while (str[i] != '.' && !ft_isspecific(str[i]))
	{
		if (ft_isdigit(str[i]) && !p->width)
			p->width = ft_atoi(str + i);
		++i;
	}
}

static void	ft_parse_precision(const char *str, t_format *p, int i)
{
	p->dot = 1;
	p->precision = ft_atoi(&str[i + 1]);
	p->neg_prec = p->precision < 0;
}
