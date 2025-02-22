/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:07:45 by yslami            #+#    #+#             */
/*   Updated: 2025/02/21 17:30:52 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree	*build_ast(t_token *token)
{
	t_token	*curr;
	t_token	*save;

	curr = last_token(token);
	while (curr && curr->visited != 1)
	{
		skip_brackets_prev(&curr);
		save = curr;
		if (curr && curr->visited != 1 && curr->type  == OPEN_BRACKET)
			curr = curr->prev;
		if (curr && curr->visited != 1 && islogical(curr->type))
			return (found_logical(curr));
		if (curr)
			curr = curr->prev;
	}
	return (fetch_pipe_or_subshell(save));
}

t_tree	*fetch_pipe_or_subshell(t_token *token)
{
	t_token	*curr;
	int		bracket;

	curr = token;
	bracket = 0;
	while (curr && curr->visited != 1)
	{
		skip_brackets_next(&curr, &bracket);
		if (curr && curr->visited != 1 && curr->type == PIPE)
			return (found_pipe(curr, bracket));
		if (curr)
			curr = curr->next;
	}
	if (bracket)
		return (create_subshell(token));
	return (create_cmd(token));
}

t_tree	*found_logical(t_token *token)
{
	t_tree	*node;

	node = create_node(token);
	node->right = fetch_pipe_or_subshell(token->next);
	node->left = build_ast(back_prev(token->prev));
	return (node);
}

t_token	*back_prev(t_token *token)
{
	while (token && token->prev && token->prev->visited != 1)
		token = token->prev;
	return (token);
}

t_tree	*found_pipe(t_token *token, int subshell)
{
	t_tree	*node;

	node = create_node(token);
	node->right = fetch_pipe_or_subshell(token->next);
	if (!subshell)
		node->left = create_cmd(left_back(token->prev));// should be here left_back
	else
		node->left = create_subshell(token->prev);
	return (node);
}

t_token *left_back(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr && curr->visited != 1 && curr->prev && \
		curr->prev->visited != 1)
	{
		curr = curr->prev;
	}
	return (curr);
}

t_tree	*create_node(t_token *token)
{
	t_tree	*node;

	if (!token)
		return (NULL);
	node = (t_tree *)malloc(sizeof(t_tree));
	node->type = get_tree_type(token->type);
	node->args = NULL;// when its T_SUB this should be filled
	node->left = NULL;
	node->right = NULL;
	token->visited = 1;
	return (node);
}

void	skip_brackets_prev(t_token **token)
{
	int	level;

	if ((*token)->type == CLOSED_BRACKET)
	{
		level = 1;
		(*token) = (*token)->prev;
		while ((*token) && (*token)->visited != 1 && level)
		{
			if ((*token)->type == OPEN_BRACKET)
				level--;
			else if ((*token)->type == CLOSED_BRACKET)
				level++;
			if (!level)
				break ;
			(*token) = (*token)->prev;
		}
	}
}

void	skip_brackets_next(t_token **token, int *has_brackets)
{
	int	level;

	if ((*token) && (*token)->type == OPEN_BRACKET)
	{
		level = 1;
		(*token)->visited = 1;
		level = 1;
		if (has_brackets)
			*has_brackets = 1;
		(*token) = (*token)->next;
		while ((*token) && (*token)->visited != 1 && level)
		{
			if ((*token)->type == OPEN_BRACKET)
				level++;
			else if ((*token)->type == CLOSED_BRACKET)
				level--;
			if (!level)
				break;
			(*token) = (*token)->next;
		}
		if (*token && (*token)->type == CLOSED_BRACKET)
			(*token)->visited = 1;
	}
}

t_tree	*create_subshell(t_token *token)
{
	t_tree	*node;
	t_args	*args;

	// node = create_node(token);
	if(!token)
		return (NULL);
	printf("%s\n", token->value);
	node = (t_tree *)malloc(sizeof(t_tree));
	node->type = T_SUBSHELL;
	args = (t_args *)malloc(sizeof(t_args));
	extract_args(args, token);
	node->args = args;
	node->left = build_ast(token);
	node->right = NULL;
	return (node);
}

t_tree	*create_cmd(t_token *token)
{
	t_tree	*node;
	t_args	*args;

	if(!token)
		return (NULL);
	node = (t_tree *)malloc(sizeof(t_tree));
	node->type = T_CMD;
	args = (t_args *)malloc(sizeof(t_args));
	extract_args(args, token);
	node->args = args;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	extract_args(t_args *args, t_token *token)
{
	t_token	*curr;
	char	**res;
	t_redir	*redir = NULL;
	int		i = 0;
	int		arg_count = 0;

	curr = token;

	while (curr && curr->visited != 1)
	{
		if (isredirect(curr->type))
		{
			if (curr->next) // Skip the filename
				curr = curr->next;
		}
		else
		{
			arg_count++;
		}
		curr = curr->next;
	}

	printf("arg_count: %d\n", arg_count);

	res = (char **)malloc((arg_count + 1) * sizeof(char *));

	curr = token;
	while (curr && curr->visited != 1)
	{
		if (isredirect(curr->type))
			handle_redirection(&redir, &curr);
		else
		{
			res[i] = quoted_process(&curr);
			if (res[i])
				i++;
		}
	}
	res[i] = NULL;
	args->argv = res;
	args->redir = redir;
}

t_redir	*create_redir_node(int type, char *filename)
{
	t_redir	*new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = get_redir_type(type);
	new_redir->filename = filename;
	new_redir->next = NULL;
	return (new_redir);
}

t_redir_type	get_redir_type(int type)
{
	if (type == REDIR_IN)
		return (R_REDIR_IN);
	if (type == REDIR_OUT)
		return (R_REDIR_OUT);
	if (type == REDIR_APPEND)
		return (R_REDIR_APPEND);
	return (R_HEREDOC);
}

void	append_redir_node(t_redir **redir_list, t_redir *new_redir)
{
	t_redir	*curr;

	if (!*redir_list)
	{
		*redir_list = new_redir;
		return ;
	}
	curr = *redir_list;
	while (curr->next)
		curr = curr->next;
	curr->next = new_redir;
}

void	handle_redirection(t_redir **redir_list, t_token **curr)
{
	t_redir	*new_redir;

	if (!curr || !(*curr) || !isredirect((*curr)->type))
		return ;

	int type = (*curr)->type;
	*curr = (*curr)->next; // Move to filename

	if (*curr)
	{
		char *filename = quoted_process(curr);
		new_redir = create_redir_node(type, filename);
		if (new_redir)
			append_redir_node(redir_list, new_redir);
	}
}

t_tree_type get_tree_type(int type)
{
	if (type == AND)
		return (T_AND);
	if (type == OR)
		return (T_OR);
	return (T_PIPE);
}
