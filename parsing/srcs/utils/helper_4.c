/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:26:48 by yslami            #+#    #+#             */
/*   Updated: 2025/02/22 12:01:32 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_quote(enum e_token_type type)
{
	if (type == D_Q || type == S_Q)
		return (1);
	return (0);
}

int is_regular(enum e_token_type type)
{
	if (type == EXPR || type == DOLLAR || is_quote(type))
		return (1);
	return (0);
}
