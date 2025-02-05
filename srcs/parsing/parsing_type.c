/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:05:43 by yslami            #+#    #+#             */
/*   Updated: 2025/02/04 19:15:29 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_space(t_vars **vars, int *ret)
{
	char	c;

	c = (*vars)->cmd[(*vars)->i];
	while (c && !isquote(c) && !special_d(c) && isspace(c))
	{
		(*vars)->i++;
		c = (*vars)->cmd[(*vars)->i];
	}
	*ret = 0;
}

void	parse_char(t_token **token, t_vars **vars, int *ret)
{
	char	c;
	int		spaceafter;

	(*vars)->tmp = (*vars)->i;
	c = (*vars)->cmd[(*vars)->i];
	while (c && !isquote(c) && !special_d(c) && !isspace(c) && \
		!isparenthesis(c))
	{
		(*vars)->i++;
		c = (*vars)->cmd[(*vars)->i];
	}
	spaceafter = before_space((*vars)->cmd, (*vars)->tmp - 1);
	if ((*vars)->flag == 1)
	{
		(*token)->value = ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp);
		(*token)->spaceafter = spaceafter;
		(*vars)->flag = 0;
	}
	else
		ft_newnode(token, ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp), spaceafter);
	*ret = 0;
}

int	parse_quote(t_token **token, t_vars **vars, int *ret)
{
	char	quote;
	int		spaceafter;

	(*vars)->tmp = (*vars)->i;
	if (isquote((*vars)->cmd[(*vars)->i]))
		quote = (*vars)->cmd[(*vars)->i++];
	while ((*vars)->cmd[(*vars)->i] && (*vars)->cmd[(*vars)->i] != quote)
		(*vars)->i++;
	if (isquote((*vars)->cmd[(*vars)->i++]))
	{
		spaceafter = before_space((*vars)->cmd, (*vars)->tmp - 1);
		if ((*vars)->flag == 1)
		{
			(*token)->value = ft_substr((*vars)->cmd, (*vars)->tmp, \
				(*vars)->i - (*vars)->tmp);
			(*token)->spaceafter = spaceafter;
			(*vars)->flag = 0;
		}
		else
			ft_newnode(token, ft_substr((*vars)->cmd, (*vars)->tmp, \
				(*vars)->i - (*vars)->tmp), spaceafter);
	}
	else
		return (*ret = 1, perror("minishell: open quotes!"), 1);
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
			(isalnum((*vars)->cmd[(*vars)->i]) == 1))
			(*vars)->i++;
	bef_space = before_space((*vars)->cmd, (*vars)->tmp - 1);
	if ((*vars)->flag == 1)
	{
		(*token)->value = ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp);
		(*token)->spaceafter = bef_space;
		(*vars)->flag = 0;
	}
	else
		ft_newnode(token, ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp), bef_space);
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
		!ft_isquote((*vars)->cmd[(*vars)->i]) && \
		!ft_isspace((*vars)->cmd[(*vars)->i]) && \
		count++ < 2 && curr_sep == (*vars)->cmd[(*vars)->i])
		(*vars)->i++;
	bef_space = before_space((*vars)->cmd, (*vars)->tmp - 1);
	if ((*vars)->flag == 1)
	{
		(*token)->value = ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp);
		(*token)->spaceafter = bef_space;
		(*vars)->flag = 0;
	}
	else
		ft_newnode(token, ft_substr((*vars)->cmd, (*vars)->tmp, \
			(*vars)->i - (*vars)->tmp), bef_space);
	*ret = 0;
}

void	parse_parenthesis(t_token **token, t_vars **vars, int *ret)
{
	
}
