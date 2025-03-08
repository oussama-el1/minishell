/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:41:55 by yslami            #+#    #+#             */
/*   Updated: 2025/03/08 02:36:44 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_her(t_redir *herdc)
{
	while (herdc)
	{
		herdoc_loop(herdc->heredoc_delim, 0, -1, 0);
		herdc = herdc->next;
	}
}
