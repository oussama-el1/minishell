/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:17:23 by yslami            #+#    #+#             */
/*   Updated: 2025/03/12 04:31:42 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*input_cmd(t_token *token)
{
	char	*line;

	if (!token)
		return (NULL);
	line = NULL;
	if (token->type == AND)
		line = readline("cmdand> ");
	else if (token->type == OR)
		line = readline("cmdor> ");
	else if (token->type == PIPE)
		line = readline("cmdpipe> ");
	return (line);
}

void	process_token(t_token **curr, t_args *args, t_redir **redir, int *i)
{
	if (isredirect((*curr)->type))
		handle_redirection(redir, curr);
	args->argv[*i] = quoted_process(curr, &args->expand_list[*i], \
		&args->wildcards[*i]);
	if (args->argv[*i])
		(*i)++;
}

void	concat_str(char **arg, char *tmp, int bef_space)
{
	if (*arg && !bef_space)
		*arg = ft_strjoin(*arg, tmp, CMD);
	else
		*arg = ft_strdup(tmp, CMD);
}

int	contains_unquoted_ampersand(const char *str)
{
	int	single_q;
	int	double_q;
	int	i;

	single_q = 0;
	double_q = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (str[i] == '"' && !single_q)
			double_q = !double_q;
		else if (str[i] == '&' && !single_q && !double_q)
			return (1);
		i++;
	}
	return (0);
}
