/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:41:55 by yslami            #+#    #+#             */
/*   Updated: 2025/03/09 02:53:30 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_her(t_redir *herdc, t_helper *hp)
{
	int	i;

	i = 0;
	while (herdc && i++ < hp->tour)
		herdc = herdc->next;
	while (herdc)
	{
		handle_heredoc(herdc->heredoc_delim, hp);
		hp->tour++;
		herdc = herdc->next;
	}
}
