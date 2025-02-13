/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:07:45 by yslami            #+#    #+#             */
/*   Updated: 2025/02/12 21:53:32 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// statuic void	find_lowest_precedence_operator(t_token *token, t_token **op_token)
// {

// }

// static t_tree	*search_parse(t_token *token)
// {
// 	t_token	*op_token;

// 	op_token = NULL;
// 	find_lowest_precedence_operator(last_token(token), &op_token);
// 	if (op_token)
// 		return (create_node_recursive(op_token));
// 	return (parse_command_or_sub(token));
// }

// t_tree	*build_ast(t_token *token)
// {
// 	if (!token)
// 		return (NULL);
// 	return (search_parse(token));
// }

// echo hello | grep d

/*
static t_tree	*parse_and_or(t_token *token);
static void		recursive_parsing(t_token *token, t_tree **node);

t_tree	*build_ast(t_token *token)
{
	return (parse_and_or(token));
}

static t_tree	*parse_and_or(t_token *token)
{
	t_token	*tmp;
	t_tree	*node;

	node = NULL;
	while (token && token->visited != 1)
	{
		// skip_parenthesis_back(&token);
		tmp = token;
		// if (token && token->visited != 1 && token->type == OPEN_BRACKET)
			// token = token->prev;
		if (token && token->visited != 1 && (token->type == AND || \
			token->type == OR))
			return (recursive_parsing(token, &node), node);
		if (token)
			token = token->prev;
	}
	return (find_pipe(token));
}

static void	recursive_parsing(t_token *token, t_tree **node)
{
	(*node) = create_tree_node(token, 1);
	(*node)->right = find_pipe(token->next);
	(*node)->left = parse_and_or(token->prev);
}

static t_tree	*find_pipe(t_token *token)
{
	t_tree	*node;

	if (!token)
		return (NULL);
	node = NULL;
	while (token && token->visited != 1)
	{
		// skip_parenthesis_next(&token) // still need an integer as refernece of brackets existence
		if (token && token->visited != 1 && token->type == PIPE)
			return ();
	}
}


t_tree	*search_pipe(t_token *token)
{
	t_token	*save;
	t_tree	*node;
	int		is_brackets;

	node = NULL;
	if (!token)
		return (node);
	is_brackets = 0;
	while (token && token->visited != 1)
	{
		token = skip_brackets_next(token, &is_brackets);
		save = token;
		if (token && token->visited != 1 && token->type == TOKEN_CLOSED_BRACKET)
			token->visited = 1;
		if (token && token->visited != 1 && token->type == TOKEN_PIPE)
			return (choose_function(node, token, is_brackets));// we are here
		if (token)
			token = token->next;
	}
	if (is_brackets)
		return (search_logical_operator(save->prev));
	return (make_command(save));
}

static t_tree	*make_command(t_token *token)
{
	t_tree	*node;
	t_cmd	*cmd;

	if (!token)
		return (NULL);
	while (token->prev && token->prev->visited != 1)
		token = token->prev;
	if (!token)
		return (NULL);
	node = make_node(&token, 0);
	node->next = make_cmd(token);
	cmd = node->next;
	token = token->next;
	while (token && token->visited != 1)
	{
		add_cmd(&cmd, token);
		token = token->next;
	}
	return (node);
}

static t_tree	*choose_function(t_tree *node, t_token *token, int is_brackets)
{
	node = make_node(&token, 1);
	if (is_brackets)
		node->left = search_logical_operator(token->prev->prev);
	else
		node->left = make_command(token->prev);
	node->right = search_pipe(token->next);
	return (node);
}


*/
