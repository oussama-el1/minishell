/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:00:32 by yslami            #+#    #+#             */
/*   Updated: 2025/03/12 01:27:26 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*create_subshell(t_token *token)
{
	t_tree	*node;
	t_args	*args;

	if (!token)
		return (NULL);
	node = (t_tree *)maroc(sizeof(t_tree), ALLOC, CMD);
	node->type = T_SUBSHELL;
	args = NULL;
	extract_subshell_args(&args, token);
	node->args = args;
	node->left = build_ast(token);
	node->right = NULL;
	return (node);
}

t_tree	*create_cmd(t_token *token)
{
	t_tree	*node;
	t_args	*args;

	if (!token)
		return (NULL);
	node = (t_tree *)maroc(sizeof(t_tree), ALLOC, CMD);
	node->type = T_CMD;
	args = (t_args *)maroc(sizeof(t_args), ALLOC, CMD);
	extract_args(args, token);
	node->args = args;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	extract_args(t_args *args, t_token *token)
{
	t_token	*curr;
	t_redir	*redir;
	int		i;
	int		arg_count;

	arg_count = args_count(token);
	args->argv = (char **)maroc((arg_count + 1) * sizeof(char *), ALLOC, CMD);
	args->wildcards = (bool *)maroc((arg_count + 1) * sizeof(bool), ALLOC, CMD);
	args->expand_list = (t_expand **)maroc((arg_count + 1) * \
		sizeof(t_expand *), ALLOC, CMD);
	curr = token;
	i = 0;
	redir = NULL;
	while (curr && curr->visited != 1)
		process_token(&curr, args, &redir, &i);
	args->argv[i] = NULL;
	args->expand_list[i] = NULL;
	args->wildcards[i] = false;
	args->redir = redir;
	args->herdoc_file = NULL;
	args->herdoc_idx = -1;
}

t_tree_type	get_tree_type(int type)
{
	if (type == AND)
		return (T_AND);
	if (type == OR)
		return (T_OR);
	return (T_PIPE);
}

void	extract_subshell_args(t_args **args, t_token *token)
{
	t_token	*curr;
	t_redir	*redir;

	redir = NULL;
	curr = token;
	skip_brackets_next(&curr, NULL);
	if (curr && curr->type == CLOSED_BRACKET)
		curr = curr->next;
	while (curr && curr->visited != 1)
	{
		if (isredirect(curr->type))
			handle_redirection(&redir, &curr);
		else
			curr = curr->next;
	}
	if (redir)
	{
		*args = (t_args *)maroc(sizeof(t_args), ALLOC, CMD);
		(*args)->redir = redir;
		(*args)->argv = NULL;
		(*args)->herdoc_file = NULL;
		(*args)->herdoc_idx = -1;
	}
}
