/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:10:10 by yslami            #+#    #+#             */
/*   Updated: 2025/02/04 15:20:12 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	isalnum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || \
		(c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	isspace(char c)
{
	if ((c >= 9 && c <= 13) ||c == 32)
		return (1);
	return (0);
}

int	isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	special_d(char c)
{
	if (c == '>' || c == '<' || c == '$' || \
		c == '|' || c == '&')
		return (1);
	return (0);
}

int	isparenthesis(char c)
{
	if (c == '(' || c == ')')
		return (1);
	return (0);
}
