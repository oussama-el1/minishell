/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:13:20 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/21 17:24:34 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	tokenizer(t_token **token, t_vars *vars);
static void	give_type(t_token **token);

/*

const char *token_type_names[] = {
	"REDIR_IN",
	"REDIR_OUT",
	"REDIR_APPEND",
	"HEREDOC",
	"PIPE",
	"AND",
	"OR",
	"DOLLAR",
	"OPEN_BRACKET",
	"CLOSED_BRACKET",
	"D_Q",
	"S_Q",
	"EXPR",
};
*/

const char *type_names[] = {
   "T_AND",
	"T_OR",
	"T_PIPE",
	"T_CMD",
	"T_SUBSHELL",
};

const char *token_type_names[] = {
	"REDIR_IN",
	"REDIR_OUT",
	"REDIR_APPEND",
	"HEREDOC",
	"PIPE",
	"AND",
	"OR",
	"DOLLAR",
	"OPEN_BRACKET",
	"CLOSED_BRACKET",
	"D_Q",
	"S_Q",
	"EXPR",
};

static void print_redir_list(t_redir *redir)
{
    while (redir)
    {
        printf("  -> Redir: Type = %s, Filename = \"%s\"\n",
               token_type_names[redir->type], redir->filename);
        redir = redir->next;
    }
}

static void print_ast(t_tree *node, int depth, const char *relation)
{
    if (!node)
        return;

    // Indentation for tree depth visualization
    for (int i = 0; i < depth; i++)
        printf("  ");

    // Print node type using the global array and relation (Left/Right)
    printf("[%s] Node: %s", relation, type_names[node->type]);

    // If the node is a command, print its argv
    if (node->type == T_CMD && node->args)
    {
        printf(" (argv: ");
        for (int i = 0; node->args->argv[i]; i++)
        {
            printf("\"%s\"", node->args->argv[i]);
            if (node->args->argv[i + 1])
                printf(", "); // Print comma between arguments
        }
        printf(")");

        // Print redirections if any exist
        if (node->args->redir)
        {
            printf("\n");
            print_redir_list(node->args->redir);
        }
    }

    printf("\n");

    // Recursively print left and right children with proper relation
    if (node->left)
        print_ast(node->left, depth + 1, "Left");
    if (node->right)
        print_ast(node->right, depth + 1, "Right");
}

void	process_input(char *line, t_token **token, t_env *env_list)
{
	t_tree	*tree;
	t_vars	*vars;

	init_vars(&vars, line, env_list);
	if (tokenizer(token, vars) == 0)
	{
		give_type(token);
		if (!check_syntax(*token, 0))
			return ;
		// new_token = join_heredocargs(*token);
		// process_tokens(*token, env_list);
		tree = build_ast(*token);

		printf("\n===== AST Structure =====\n");
		print_ast(tree, 0, "Root");
		printf("=========================\n\n");
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
