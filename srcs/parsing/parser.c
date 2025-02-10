/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:13:20 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/09 19:08:30 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	tokenizer(t_token **token, t_vars *vars);
static void	give_type(t_token **token);

void	process_input(char *line, t_token **token, t_env *env_list)
{
	t_tree	*tree;
	t_vars	*vars;
	t_token	*new_token;

	init_vars(&vars, line, env_list);
	if (tokenizer(token, vars) == 0)
	{
		new_token = join_heredocargs(*token);
		give_type(&new_token);
		if (!check_syntax(&new_token))
			return ;

		tree = build_tree(token);
		// execute(tree, env_list);
	}
	free(line);
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
