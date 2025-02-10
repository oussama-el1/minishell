
#include "../../inc/minishell.h"

static void	new_heredoc_node(t_token **token, t_joinheredoc **arg);
static void	add_normal_arg(t_token **new, t_token **token, t_joinheredoc **arg);
static void	start_heredoc(t_token **new, t_token **token, t_joinheredoc **arg);
static void	heredoc_join(t_token **token, t_joinheredoc **arg);

t_token	*join_heredocargs(t_token *token)
{
	t_joinheredoc	*arg;
	t_token			*new_token;

	arg = (t_joinheredoc *)malloc(sizeof(t_joinheredoc));
	arg->flag = 1;
	arg->heredoc_flag = 0;
	while (token)
	{
		if (token->value[0] == '<' && token->value[1] == '<' && \
			token->next && !special_d_1(token->next->value[0]))
		{
			start_heredoc(&new_token, &token, &arg);
			while (token && token->bef_space != 1 && \
				!special_d_1(token->value[0]) && !isparenth(token->value[0]))
				heredoc_join(&token, &arg);
			new_heredoc_node(&new_token, &arg);
		}
		else
		{
			add_normal_arg(&new_token, &token, &arg);
		}
		arg->buffer = NULL;
	}
	return (new_token);
}

static void	heredoc_join(t_token **token, t_joinheredoc **arg)
{
	if (isquote((*token)->value[0]))
		(*arg)->buffer = ft_strjoin((*arg)->buffer, \
			remove_quotes((*token)->value));
	else if ((*token)->value[0] == '$' && !(*token)->value[1] && \
		(*token)->next && !isquote((*token)->next->value[0]))
		(*arg)->buffer = ft_strjoin((*arg)->buffer, (*token)->value);
	else
		(*arg)->buffer = ft_strjoin((*arg)->buffer, (*token)->value);
	(*token) = (*token)->next;
}

static void	start_heredoc(t_token **new, t_token **token, t_joinheredoc **arg)
{
	(*arg)->buffer = ft_strdup((*token)->value);
	(*arg)->bef_space = (*token)->bef_space;
	new_heredoc_node(new, arg);
	(*arg)->buffer = NULL;
	(*token) = (*token)->next;
	(*arg)->bef_space = (*token)->bef_space;
	(*token)->bef_space = 0;
	(*arg)->heredoc_flag = 0;
}

static void	add_normal_arg(t_token **new, t_token **token, t_joinheredoc **arg)
{
	(*arg)->bef_space = (*token)->bef_space;
	(*arg)->buffer = ft_strdup((*token)->value);
	new_heredoc_node(new, arg);
	(*token) = (*token)->next;
}

static void	new_heredoc_node(t_token **token, t_joinheredoc **arg)
{
	t_token	*new_token;
	t_token	*curr;

	new_token = (t_token *)malloc(sizeof(t_token));
	curr = *token;
	new_token->value = (*arg)->buffer;
	new_token->bef_space = (*arg)->bef_space;
	new_token->bef_space = (*arg)->heredoc_flag;
	new_token->visited = 0;
	new_token->next = NULL;
	if ((*arg)->flag == 1)
	{
		new_token->prev = NULL;
		*token = new_token;
		(*arg)->flag = 0;
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		new_token->prev = curr;
		curr->next = new_token;
	}
}
