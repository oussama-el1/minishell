/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:05:21 by yslami            #+#    #+#             */
/*   Updated: 2025/02/22 12:02:04 by yslami           ###   ########.fr       */
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
		if (isredirect(curr->type))
		{
			if (curr->next)
				curr = curr->next;
		}
		else
		{
			arg_count++;
		}
		curr = curr->next;
	}
	return (arg_count);
}
