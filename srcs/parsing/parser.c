/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 01:01:04 by yslami            #+#    #+#             */
/*   Updated: 2025/03/16 07:15:47 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenizer(t_token **token, t_vars *vars);
static int	end_with_operator(char *line);
static void	give_type(t_token **token);
static int	handle_end_of_line(char **line, t_token **token, \
	t_helper *helper);

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
		if (redir->type != R_HEREDOC)
        	printf("  -> Redir: Type = %s, Filename = \"%s\"\n",
               		token_type_names[redir->type], redir->filename);
		else
			printf("  -> Redir: Type = %s, Delimiter = \"%s\"\n",
               		token_type_names[redir->type], redir->h_del);
		for (t_expand *tmp = redir->expand_list; tmp; tmp = tmp->next)
		{
			 printf("  -> Expand: Start = %zu, End = %zu, Expanded = %s\n",
               tmp->start, tmp->end, tmp->expanded ? "true" : "false");
		}
        redir = redir->next;
    }
}

static void print_expand_list(t_expand *expand)
{
    while (expand)
    {
        printf("   type = %s  -> Expand: Start = %zu, End = %zu, Expanded = %s\n",
               token_type_names[expand->type], expand->start, expand->end, expand->expanded ? "true" : "false");
        expand = expand->next;
    }
}

void print_ast(t_tree *node, int depth, const char *relation)
{
    if (!node)
        return;

    // Print indentation based on the depth
    for (int i = 0; i < depth; i++)
        printf("  ");

    // Print node type
    printf("[%s] Node: %s", relation, type_names[node->type]);

    // If it's a command or subshell, print arguments and redirections
    if ((node->type == T_CMD || node->type == T_SUBSHELL) && node->args)
    {
        if (node->type != T_SUBSHELL)
        {
            // Print arguments
            printf(" (argv: ");
            for (int i = 0; node->args->argv[i]; i++)
            {
                printf("\"%s\"", node->args->argv[i]);
                if (node->args->argv[i + 1])
                    printf(" : ");
            }
            printf(")");
        }

        // Print expansion list if it exists
        if (node->args->expand_list)
        {
            printf("\n");
            for (int i = 0; node->args->argv[i]; i++)
            {
                if (node->args->expand_list[i])
                {
                    printf("  -> Arg[%d]: \"%s\" Expansion Details:\n", i, node->args->argv[i]);
                    print_expand_list(node->args->expand_list[i]);
                }
            }
        }

        // Print redirections if they exist
        if (node->args->redir)
        {
            printf("\n");
            print_redir_list(node->args->redir);
        }

		// print wildcards bool array
		for (int i = 0; node->args->argv[i]; i++)
		{
			printf("  -> Arg[%d]: \"%s\" Wildcard: %s\n", i, node->args->argv[i], node->args->wildcards[i] ? "true" : "false");
		}
    }

    printf("\n");

    // Recursively print left and right children (if any)
    if (node->left)
        print_ast(node->left, depth + 1, "Left");
    if (node->right)
        print_ast(node->right, depth + 1, "Right");
}

int	process_input(char *line, t_token **token, t_helper *helper, \
	int base)
{
	t_vars	*vars;

	init_vars(&vars, line);
	init_token(token, 0);
	if (tokenizer(token, vars) == 0)
	{
		give_type(token);
		if (!check_syntax(*token))
			return (add_history(line), 0);
		if (!handle_end_of_line(&line, token, helper))
			return (add_history(line), 0);
		if (!base)
			return (1);
		helper->node = build_ast(*token);
		signal(SIGINT, SIG_IGN);
		execute_herdocs(helper);
		// printf("g_signals.sigint_heredoc: %d\n", g_signals.sigint_heredoc);
		if (g_signals.sigint_heredoc)
		{
			g_signals.sigint_heredoc = 0;
			return (0);
		}
		execute_ast(helper);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		return (add_history(line), 0);
	return (1);
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
	new_line = input_cmd(last_token(*token));
	if (!new_line)
	{
		if (g_exit_status == 130)
			return (0);
		printf("minishell: syntax error: unexpected end of file\n");
		g_exit_status = 2;
		return (0);
	}
	*line = ft_strjoin(*line, " ", CMD);
	*line = ft_strjoin(*line, new_line, CMD);
	free(new_line);
	return (process_input(*line, token, helper, 0));
}
