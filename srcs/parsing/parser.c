
#include "../../inc/minishell.h"

static int	tokenizer(t_token **token, t_vars *vars);
static int	end_with_operator(char *line);
static void	give_type(t_token **token);
static int	handle_end_of_line(char **line, t_token **token, t_tree **tree);

void	process_input(char *line, t_token **token, t_tree **tree)
{
	t_vars	*vars;

	init_vars(&vars, line);
	init_token(token, 0);
	if (tokenizer(token, vars) == 0)
	{
		give_type(token);
		if (!check_syntax(*token, 0))
			return (add_history(line), (void)0);
		if (handle_end_of_line(&line, token, tree))
			return ;
		if (line)
			add_history(line);
		*tree = build_ast(*token);
		// printf("\n===== AST Structure =====\n");
		// print_ast(*tree, 0, "Root");
		// printf("=========================\n\n");
	}
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

static int end_with_operator(char *line)
{
	size_t	len;

	if (!line || !*line)
		return (0);
	len = ft_strlen_0(line);
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

static int	handle_end_of_line(char **line, t_token **token, t_tree **tree)
{
	char	*new_line;

	while (end_with_operator(*line))
	{
		new_line = readline("> ");
		if (!new_line)
			return (ft_printf("Error\nReadline Error!\n"), 1);
		*line = ft_strjoin(*line, " ");
		*line = ft_strjoin(*line, new_line);
		free(new_line);
		process_input(*line, token, tree);
		return (1);
	}
	return (0);
}

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
        printf("  -> Expand: Start = %zu, End = %zu, Expanded = %s\n",
               expand->start, expand->end, expand->expanded ? "true" : "false");
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
    }

    printf("\n");

    // Recursively print left and right children (if any)
    if (node->left)
        print_ast(node->left, depth + 1, "Left");
    if (node->right)
        print_ast(node->right, depth + 1, "Right");
}
