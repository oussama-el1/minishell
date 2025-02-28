/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:41:22 by yslami            #+#    #+#             */
/*   Updated: 2025/02/02 16:11:01 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list		list;
	t_format	p;

	p = ft_newformat();
	va_start(list, format);
	ft_parse_bonus(format, list, &p);
	va_end(list);
	return (p.len);
}
