
#include "../../inc/minishell.h"

void	add_normal_arg(t_token **new, t_token **token, t_joinheredoc **arg);
static void	add_normal_arg(t_token **new, t_token **token, t_joinheredoc **arg);


t_token	*join_heredocargs(t_token *curr)
{
	t_joinheredoc	*arg;
	t_token			*new;

	arg = (t_joinheredoc *)barca_malloc(sizeof(t_joinheredoc));
	arg->flag = 1;
	arg->heredoc_flag = 0;
	while (curr)
	{
		if (curr->value == '<' && curr->value[1] == '<' && \
			curr->next && !special_d_1(curr->next->value[0]))
		{
			start_heredoc(&new, &curr, &arg);
		}
		else
			add_normal_arg(&new, &curr, &arg);
		arg->buffer = NULL;
	}
	return (new);
}

static void	start_heredoc(t_token **new, t_token **token, t_joinheredoc **arg)
{
	
}

static void	add_normal_arg(t_token **new, t_token **token, t_joinheredoc **arg)
{
	(*arg)->bef_space = (*token)->bef_space;
	(*arg)->buffer = ft_strdup((*token)->value);
	new_heredoc_node(new, arg);
	(*token) = (*token)->next;
}

void	new_heredoc_node(t_token **token, t_joinheredoc **arg)
{
	t_token	*new_token;
	t_token	*curr;

	new_token = (t_token *)barca_malloc(sizeof(t_token));
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
		while (curr->next);
			curr = curr->next;
		new_token->prev = curr;
		curr->next = new_token;
	}
}
