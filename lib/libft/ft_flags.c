/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:14:04 by yslami            #+#    #+#             */
/*   Updated: 2025/02/02 16:14:29 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_format	ft_newformat(void)
{
	t_format	new_p;

	new_p.len = 0;
	new_p.dot = 0;
	new_p.minus = 0;
	new_p.plus = 0;
	new_p.neg = 0;
	new_p.width = 0;
	new_p.precision = -1;
	new_p.neg_prec = 0;
	new_p.specifier = 0;
	new_p.sharp = 0;
	new_p.space = 0;
	new_p.zero = 0;
	return (new_p);
}

void	ft_reset_format(t_format *p)
{
	p->neg = 0;
	p->specifier = 0;
	p->minus = 0;
	p->plus = 0;
	p->width = 0;
	p->precision = -1;
	p->neg_prec = 0;
	p->zero = 0;
	p->dot = 0;
	p->space = 0;
	p->sharp = 0;
}

void	ft_flags_minus(t_format *p)
{
	p->minus = 1;
	p->zero = 0;
}
