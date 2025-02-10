/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:07:45 by yslami            #+#    #+#             */
/*   Updated: 2025/02/09 19:15:12 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree	*build_tree(t_token *token)
{

}







static t_tree	*create_node(enum e_tree_type type)
{
    t_tree	*node;

    node = malloc(sizeof(t_tree));
    if (!node)
        return (NULL);
    node->fd[0] = -1;
    node->fd[1] = -1;
    node->next = NULL;
    node->left = NULL;
    node->right = NULL;
    node->tree_type = type;
    return (node);
}

static t_cmd	*create_cmd_node(t_token *token)
{
    t_cmd	*cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->cmd = ft_strdup(token->value);
    cmd->fd[0] = -1;
    cmd->fd[1] = -1;
    cmd->word = 0;
    cmd->bef_space = token->bef_space;
    cmd->heredocfd = -1;
    cmd->expandheredoc = 0;
    cmd->expandwildcard = 0;
    cmd->ambiguous = 0;
    cmd->next = NULL;
    return (cmd);
}

static t_tree	*parse_cmd(t_token **token)
{
    t_tree	*node;
    t_cmd	*cmd;
    t_cmd	*current;

    node = create_node(T_CMD);
    if (!node)
        return (NULL);
    while (*token && (*token)->type == EXPR)
    {
        if (!node->next)
        {
            node->next = create_cmd_node(*token);
            current = node->next;
        }
        else
        {
            current->next = create_cmd_node(*token);
            current = current->next;
        }
        *token = (*token)->next;
    }
    return (node);
}

static t_tree	*parse_redirection(t_token **token)
{
    t_tree	*node;
    enum e_tree_type	type;

    if ((*token)->type == REDIR_IN)
        type = T_REDIR_IN;
    else if ((*token)->type == REDIR_OUT)
        type = T_REDIR_OUT;
    else if ((*token)->type == HEREDOC)
        type = T_HEREDOC;
    else
        type = T_REDIR_APPEND;
    node = create_node(type);
    if (!node)
        return (NULL);
    *token = (*token)->next;
    if (*token && (*token)->type == EXPR)
    {
        node->right = parse_cmd(token);
        return (node);
    }
    return (node);
}

static t_tree	*parse_subshell(t_token **token);

static t_tree	*parse_pipe(t_token **token)
{
    t_tree	*node;
    t_tree	*left;

    if ((*token)->type == OPEN_BRACKET)
    {
        *token = (*token)->next;
        left = parse_subshell(token);
        if ((*token)->type == CLOSED_BRACKET)
            *token = (*token)->next;
    }
    else
        left = parse_cmd(token);
    if (*token && (*token)->type == PIPE)
    {
        node = create_node(T_PIPE);
        node->left = left;
        *token = (*token)->next;
        node->right = parse_pipe(token);
        return (node);
    }
    return (left);
}

static t_tree	*parse_and_or(t_token **token)
{
	t_tree	*node;
	t_tree	*left;

	left = parse_pipe(token);
	while (*token && ((*token)->type == AND || (*token)->type == OR))
	{
		node = create_node((*token)->type == AND ? T_AND : T_OR);
		node->left = left;
		*token = (*token)->next;
		node->right = parse_pipe(token);
		left = node;
	}
	return (left);
}

static t_tree	*parse_subshell(t_token **token)
{
	return (parse_and_or(token));
}

t_tree	*build_ast(t_token *token)
{
	return (parse_and_or(&token));
}
