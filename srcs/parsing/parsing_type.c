/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:05:43 by yslami            #+#    #+#             */
/*   Updated: 2025/03/17 05:49:52 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_char(t_token **token, t_vars **vars, int *ret)
{
	char	c;
	int		bef_space;

	(*vars)->tmp = (*vars)->i;
	c = (*vars)->cmd[(*vars)->i];
	while (c && !isquote(c) && !special_d(c) && !is_space(c) && \
		!isparenth(c))
	{
		(*vars)->i++;
		c = (*vars)->cmd[(*vars)->i];
	}
	bef_space = before_space((*vars)->cmd, (*vars)->tmp - 1);
	if ((*vars)->flag == 1)
	{
		(*token)->value = ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp, CMD);
		(*token)->bef_space = bef_space;
		(*vars)->flag = 0;
	}
	else
		ft_newnode(token, ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp, CMD), bef_space);
	*ret = 0;
}

int	parse_quote(t_token **token, t_vars **vars, int *ret)
{
	char	quote;
	int		bef_space;

	(*vars)->tmp = (*vars)->i;
	if (isquote((*vars)->cmd[(*vars)->i]))
		quote = (*vars)->cmd[(*vars)->i++];
	while ((*vars)->cmd[(*vars)->i] && (*vars)->cmd[(*vars)->i] != quote)
		(*vars)->i++;
	if (isquote((*vars)->cmd[(*vars)->i++]))
	{
		bef_space = before_space((*vars)->cmd, (*vars)->tmp - 1);
		if ((*vars)->flag == 1)
		{
			(*token)->value = ft_substr((*vars)->cmd, (*vars)->tmp, \
				(*vars)->i - (*vars)->tmp, CMD);
			(*token)->bef_space = bef_space;
			(*vars)->flag = 0;
		}
		else
			ft_newnode(token, ft_substr((*vars)->cmd, (*vars)->tmp, \
				(*vars)->i - (*vars)->tmp, CMD), bef_space);
	}
	else
		return (*ret = 1, printf("minishell: open quotes!\n"), 1);
	return (*ret = 0, 0);
}

void	parse_dollar(t_token **token, t_vars **vars, int *ret)
{
	int	bef_space;

	(*vars)->tmp = (*vars)->i++;
	if ((*vars)->cmd[(*vars)->i] == '?')
		(*vars)->i++;
	else
		while ((*vars)->cmd[(*vars)->i] && \
			(is_alnum((*vars)->cmd[(*vars)->i]) == 1))
			(*vars)->i++;
	bef_space = before_space((*vars)->cmd, (*vars)->tmp - 1);
	if ((*vars)->flag == 1)
	{
		(*token)->value = ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp, CMD);
		(*token)->bef_space = bef_space;
		(*vars)->flag = 0;
	}
	else
		ft_newnode(token, ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp, CMD), bef_space);
	*ret = 0;
}

void	parse_separator(t_token **token, t_vars **vars, int *ret)
{
	int		count;
	char	curr_sep;
	int		bef_space;

	(*vars)->tmp = (*vars)->i;
	count = 0;
	curr_sep = (*vars)->cmd[(*vars)->i];
	while ((*vars)->cmd[(*vars)->i] && \
		special_d((*vars)->cmd[(*vars)->i]) && \
		!isquote((*vars)->cmd[(*vars)->i]) && \
		!is_space((*vars)->cmd[(*vars)->i]) && \
		count++ < 2 && curr_sep == (*vars)->cmd[(*vars)->i])
		(*vars)->i++;
	bef_space = before_space((*vars)->cmd, (*vars)->tmp - 1);
	if ((*vars)->flag == 1)
	{
		(*token)->value = ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp, CMD);
		(*token)->bef_space = bef_space;
		(*vars)->flag = 0;
	}
	else
		ft_newnode(token, ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp, CMD), bef_space);
	*ret = 0;
}

void	parse_parenthesis(t_token **token, t_vars **vars, int *ret)
{
	int		bef_space;

	(*vars)->tmp = (*vars)->i++;
	bef_space = before_space((*vars)->cmd, (*vars)->tmp - 1);
	if ((*vars)->flag == 1)
	{
		(*token)->value = ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp, CMD);
		(*token)->bef_space = bef_space;
		(*vars)->flag = 0;
	}
	else
		ft_newnode(token, ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp, CMD), bef_space);
	*ret = 0;
}
