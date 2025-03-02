/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:26:30 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/01 23:37:06 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int valid_option(char *option)
{
	int	i;

	i = 0;
	if (option[0] != '-')
		return (0);
	else
	{
		i++;
		while (option[i])
		{
			if (option[i] != 'n')
				return (0);
			i++;
		}
	}
	return (1);
}

int	ft_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 0;
	while (argv[i] && valid_option(argv[i]))
	{
		newline = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] && *argv[i])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
