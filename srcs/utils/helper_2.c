/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 01:22:46 by yslami            #+#    #+#             */
/*   Updated: 2025/03/08 01:10:00 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_type(const char *str)
{
	static t_token_map	token_map[] = {
	{"<", REDIR_IN}, {">", REDIR_OUT}, \
	{">>", REDIR_APPEND}, {"<<", HEREDOC}, \
	{"|", PIPE}, {"&&", AND}, {"||", OR}, \
	{"$", DOLLAR}, {"(", OPEN_BRACKET}, \
	{")", CLOSED_BRACKET}, {"\"", D_Q}, {\
	"'", S_Q}, {NULL, EXPR}
	};
	int					i;

	if (*str == '"')
		return (D_Q);
	else if (*str == '\'')
		return (S_Q);
	else if (*str == '$')
		return (DOLLAR);
	i = 0;
	while (token_map[i].key)
	{
		if (!ft_strcmp(str, token_map[i].key))
			return (token_map[i].type);
		i++;
	}
	return (EXPR);
}

int	non_control2(enum e_token_type type)
{
	if (!is_dilim(type) && !isredirect(type) && \
		type != OPEN_BRACKET && type != CLOSED_BRACKET)
		return (1);
	return (0);
}
