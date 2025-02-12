/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:02:59 by yslami            #+#    #+#             */
/*   Updated: 2025/02/02 16:11:10 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_unsign(char *num_str, t_format p);
static int	ft_print_un(char *num_str, t_format p);

int	ft_print_u(unsigned nbr, t_format p)
{
	char	*num_str;
	int		count;

	count = 0;
	if (p.precision == 0 && nbr == 0)
		return (count += ft_putnchar_fd(' ', 1, p.width));
	num_str = ft_utoa(nbr);
	if (!num_str)
		return (0);
	count += ft_print_unsign(num_str, p);
	free(num_str);
	return (count);
}

static int	ft_print_unsign(char *num_str, t_format p)
{
	int	count;

	count = 0;
	if (p.precision >= 0 && p.zero)
		p.zero = 0;
	if (p.precision == 0 || p.precision < (int)ft_strlen(num_str))
		p.precision = -1;
	if (p.minus)
		count += ft_print_un(num_str, p);
	if (p.precision >= 0)
	{
		p.width -= p.precision;
		count += ft_putnchar_fd(' ', 1, p.width);
	}
	else
		count += ft_putnchar_fd(ft_type(p), 1, p.width - ft_strlen(num_str));
	if (!p.minus)
		count += ft_print_un(num_str, p);
	return (count);
}

static int	ft_print_un(char *num_str, t_format p)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(num_str);
	if (p.precision >= 0)
		count += ft_putnchar_fd('0', 1, p.precision - len);
	count += ft_putstrn_fd(num_str, 1, len);
	return (count);
}
