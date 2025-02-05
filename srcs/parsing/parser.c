/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:13:20 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/04 19:15:19 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	tokenizer(t_token **token, t_vars *vars);

void	process_input(char *lie, t_token **token, t_env *env_list)
{
	// t_tree	*tree;
	t_vars	*vars;

	init_vars(&vars, lie, env_list);
	tokenizer(token, vars);
}

static int	tokenizer(t_token **token, t_vars *vars)
{
	int	ret;

	ret = 0;
	while (vars->cmd[vars->i] && !ret)
	{
		if (isspace(vars->cmd[vars->i]))
			ft_space(&vars, &ret);
		else if (isquote(vars->cmd[vars->i]))
			parse_quote(token, &vars, &ret);
		else if (vars->cmd[vars->i] == '$')
			parse_dollar(token, &vars, &ret);
		else if (special_d(vars->cmd[vars->i]))
			parse_separator(token, &vars, &ret);
		else if (isparenthesis(vars->cmd[vars->i]))
			parse_parenthesis(token, &vars, &ret);
			parse_char(token, &vars, &ret);
	}
}

/*
int	tokenizer(t_token **cmd, t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->cmd[vars->i] && i == 0)
	{
		if (ft_isspace(vars->cmd[vars->i]) == 1)
			i = (ft_space(&vars));
		else if (ft_isquote(vars->cmd[vars->i]) == 1)
			i = (ft_quote(cmd, &vars));
		else if (vars->cmd[vars->i] == '$')
			i = (ft_dollarsign(cmd, &vars));
		else if (islimiter(vars->cmd[vars->i]) == 1)
			i = (ft_separator(cmd, &vars));
		else if (vars->cmd[vars->i] == '(' || vars->cmd[vars->i] == ')')
			i = (ft_bracket(cmd, &vars));
		else
			i = (ft_char(cmd, &vars));
	}
	return (i);
}
*/




// t_token_type	get_token_type(char *token)
// {
// 	if (!ft_strncmp(token, "|", ft_strlen(token)))
// 		return (PIPE);
// 	else if (!ft_strncmp(token, "<", ft_strlen(token)))
// 		return (REDIR_IN);
// 	else if (!ft_strncmp(token, ">", ft_strlen(token)))
// 		return (REDIR_OUT);
// 	else if (!ft_strncmp(token, ">>", ft_strlen(token)))
// 		return (REDIR_APPEND);
// 	else if (!ft_strncmp(token, "<<", ft_strlen(token)))
// 		return (HEREDOC);
// 	else if (!ft_strncmp(token, "&&", ft_strlen(token)))
// 		return (LOGICAL_AND);
// 	else if (!ft_strncmp(token, "||", ft_strlen(token)))
// 		return (LOGICAL_OR);
// 	else if (token[0] == '$')
// 		return (ENV_VAR);
// 	else
// 		return (WORD);
// }
