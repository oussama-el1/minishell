/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:26:30 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/22 21:28:29 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	ft_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 0;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		newline = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
