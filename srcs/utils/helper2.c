/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 01:22:46 by yslami            #+#    #+#             */
/*   Updated: 2025/02/07 16:14:09 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	special_d_1(char c)
{
	if (c == '>' || c == '<' || c == '|' || \
		c == '&')
		return (1);
	return (0);
}

void	ft_space(t_vars **vars, int *ret)
{
	char	c;

	c = (*vars)->cmd[(*vars)->i];
	while (c && !isquote(c) && !special_d(c) && is_space(c))
	{
		(*vars)->i++;
		c = (*vars)->cmd[(*vars)->i];
	}
	*ret = 0;
}

int	before_space(char *str, int i)
{
	return (is_space(str[i]));
}
