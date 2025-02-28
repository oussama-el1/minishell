/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:05:21 by yslami            #+#    #+#             */
/*   Updated: 2025/02/27 15:52:22 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	args_count(t_token *token)
{
	t_token	*curr;
	int		arg_count;

	curr = token;
	arg_count = 0;
	while (curr && curr->visited != 1)
	{
		while (curr && curr->next && !curr->next->bef_space && \
			!isredirect(curr->next->type) && !isredirect(curr->type))
			curr = curr->next;
		if (curr && isredirect(curr->type))
		{
			curr = curr->next;
			while (curr && curr->next && !curr->next->bef_space && \
			!isredirect(curr->next->type) && !isredirect(curr->type))
			curr = curr->next;
		}
		else
			arg_count++;
		if (curr)
			curr = curr->next;
	}
	return (arg_count);
}
