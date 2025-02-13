/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:13:20 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/13 20:35:09 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	tokenizer(t_token **token, t_vars *vars);
static void	give_type(t_token **token);

/*
const char *tree_type_names[] = {
   "T_AND",
	"T_OR",
	"T_PIPE",
	"T_CMD",
	"T_REDIR_IN",
	"T_REDIR_OUT",
	"T_HEREDOC",
	"T_REDIR_APPEND",
};

const char *token_type_names[] = {
  	"EXPR",
	"REDIR_IN",
	"REDIR_OUT",
	"REDIR_APPEND",
	"HEREDOC",
	"PIPE",
	"AND",
	"OR",
	"SPACE",
	"D_Q",
	"S_Q",
	"DOLLAR",
	"OPEN_BRACKET",
	"CLOSED_BRACKET",
};

static void print_ast(t_tree *node, int depth, const char *relation)
{
    if (!node)
        return;

    // Indentation for tree depth visualization
    for (int i = 0; i < depth; i++)
        printf("  ");

    // Print node type using the global array and relation (Left/Right)
    printf("[%s] Node: %s", relation, tree_type_names[node->tree_type]);

    // Print command arguments if it's a CMD node
    if (node->tree_type == T_CMD)
    {
        t_cmd *cmd = (t_cmd *)node->next;
        printf(" [CMD]: ");
        while (cmd)
        {
            printf("%s ", cmd->cmd);
            cmd = cmd->next;
        }
    }

    printf("\n");

    // Recursively print left and right children with proper relation
    if (node->left)
        print_ast(node->left, depth + 1, "Left");
    if (node->right)
        print_ast(node->right, depth + 1, "Right");
}
*/

const char *token_type_names[] = {
  	"EXPR",
	"REDIR_IN",
	"REDIR_OUT",
	"REDIR_APPEND",
	"HEREDOC",
	"PIPE",
	"AND",
	"OR",
	"SPACE",
	"D_Q",
	"S_Q",
	"DOLLAR",
	"OPEN_BRACKET",
	"CLOSED_BRACKET",
};

void	process_input(char *line, t_token **token, t_env *env_list)
{
	// t_tree	*tree;
	t_vars	*vars;
	// t_token	*new_token;

	init_vars(&vars, line, env_list);
	if (tokenizer(token, vars) == 0)
	{
		give_type(token);

		/* print the token list */
		for (t_token *tmp = *token; tmp; tmp = tmp->next)
			printf("[%s]\t{%s}\n", token_type_names[tmp->type], tmp->value);

		if (!check_syntax(token, 0))
			return ;

		// print the token list
		for (t_token *tmp = *token; tmp; tmp = tmp->next)
			printf("[%s]\t{%s}\n", token_type_names[tmp->type], tmp->value);

		// new_token = join_heredocargs(*token);
		// // print new token list
		// for (t_token *tmp = new_token; tmp; tmp = tmp->next)
		// 	printf("[%s]\t{%s}\n", token_type_names[tmp->type], tmp->value);

		/* print tokens with before space value */
		// for (t_token *tmp = *token; tmp; tmp = tmp->next)
		// 	printf("value: %s, before space: %d\n", tmp->value, tmp->bef_space);

		//process_tokens(token);


		// tree = build_ast(*token);

		// printf("\n===== AST Structure =====\n");
		// print_ast(tree, 0, "Root");
		// printf("=========================\n\n");

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
