/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 01:22:46 by yslami            #+#    #+#             */
/*   Updated: 2025/03/12 00:19:19 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	herdoc_msg(const char *delimiter, t_helper *hp)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 1);
	ft_putnbr_fd(hp->line_count, 1);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 1);
	ft_putstr_fd((char *)delimiter, 1);
	ft_putstr_fd("')\n", 1);
}
