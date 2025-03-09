/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:41:55 by yslami            #+#    #+#             */
/*   Updated: 2025/03/09 01:57:48 by oel-hadr         ###   ########.fr       */
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
