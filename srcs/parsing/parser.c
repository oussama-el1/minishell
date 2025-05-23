/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 01:01:04 by yslami            #+#    #+#             */
/*   Updated: 2025/03/17 06:00:11 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenizer(t_token **token, t_vars *vars);
static int	end_with_operator(char *line);
static void	give_type(t_token **token);
static int	handle_end_of_line(char **line, t_token **token, \
	t_helper *helper);

int	process_input(char *line, t_token **token, t_helper *helper, \
	int base)
{
	t_vars	*vars;

	(init_vars(&vars, line), init_token(token, 0));
	if (tokenizer(token, vars) == 0)
	{
		give_type(token);
		if (!check_syntax(*token))
			return (add_history(line), 0);
		signal(SIGINT, SIG_IGN);
		if (!handle_end_of_line(&line, token, helper))
			return (add_history(line), 0);
		if (!base)
			return (1);
		helper->node = build_ast(*token);
		execute_herdocs(helper);
		if (g_signals.sigint_heredoc)
			return (g_signals.sigint_heredoc = 0, 0);
		execute_ast(helper);
	}
	return (0);
}

static int	tokenizer(t_token **token, t_vars *vars)
{
	int	ret;

	ret = 0;
	while (vars->cmd[vars->i] && !ret)
	{
		if (is_space(vars->cmd[vars->i]))
			ft_space(&vars, &ret);
		else if (isquote(vars->cmd[vars->i]))
			parse_quote(token, &vars, &ret);
		else if (vars->cmd[vars->i] == '$')
			parse_dollar(token, &vars, &ret);
		else if (special_d(vars->cmd[vars->i]))
			parse_separator(token, &vars, &ret);
		else if (isparenth(vars->cmd[vars->i]))
			parse_parenthesis(token, &vars, &ret);
		else
			parse_char(token, &vars, &ret);
		if (ret == 1)
			return (ret);
	}
	return (ret);
}

static void	give_type(t_token **token)
{
	t_token	*curr;

	curr = *token;
	while (curr)
	{
		if (curr->value && *curr->value)
			curr->type = get_type(curr->value);
		curr = curr->next;
	}
}

static int	end_with_operator(char *line)
{
	size_t	len;

	if (!line || !*line)
		return (0);
	len = ft_strlen(line);
	while (len > 0 && (line[len -1] == ' ' || line[len - 1] == '\t'))
		len--;
	if (len >= 1 && line[len - 1] == '|')
		return (1);
	if (len >= 2 && ft_strncmp(&line[len - 2], "&&", 2) == 0)
		return (1);
	if (len >= 2 && ft_strncmp(&line[len - 2], "||", 2) == 0)
		return (1);
	return (0);
}

static int	handle_end_of_line(char **line, t_token **token, t_helper *helper)
{
	char	*new_line;

	if (!end_with_operator(*line))
	{
		if (*line)
			add_history(*line);
		return (1);
	}
	signal(SIGINT, sigint_not_end);
	new_line = input_cmd(last_token(*token));
	if (!new_line)
	{
		if (g_signals.sigint_child)
		{
			g_signals.sigint_child = 0;
			return (signal(SIGINT, SIG_IGN), 0);
		}
		signal(SIGINT, handle_sigint);
		g_signals.exit_status = 2;
		return (0);
	}
	*line = ft_strjoin(*line, " ", CMD);
	*line = ft_strjoin(*line, new_line, CMD);
	(free(new_line), signal(SIGINT, handle_sigint));
	return (process_input(*line, token, helper, 0));
}
