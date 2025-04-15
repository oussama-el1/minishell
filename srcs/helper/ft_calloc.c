/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:42:39 by yslami            #+#    #+#             */
/*   Updated: 2025/03/03 00:16:17 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t nmemb, size_t size, int type)
{
	void	*ptr;

	if (size != 0 && (nmemb != (nmemb * size) / size))
		return (NULL);
	ptr = maroc(nmemb * size, ALLOC, type);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
