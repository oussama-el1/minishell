/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:16:28 by yslami            #+#    #+#             */
/*   Updated: 2025/02/02 16:16:46 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstrn_fd(char *s, int fd, int n)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s && n--)
	{
		count += ft_putchar_fd(*s, fd);
		s++;
	}
	return (count);
}
