/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:18:45 by yslami            #+#    #+#             */
/*   Updated: 2025/02/02 16:18:50 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putnchar_fd(char c, int fd, int n)
{
	int	count;

	count = 0;
	while (n-- > 0)
		count += write(fd, &c, 1);
	return (count);
}
