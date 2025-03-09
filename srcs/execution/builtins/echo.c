/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:26:30 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/08 23:49:30 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	valid_option(char *option)
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

static int	ft_strcmp_arg(char **expanded, char **argv)
{
	int	size1;
	int	size2;

	if (!expanded || !argv)
		return (0);
	size1 = 0;
	while (expanded[size1])
		size1++;
	size2 = 0;
	while (argv[size2])
		size2++;
	return (size1 != size2);
}

int	ft_echo(char **argv, char **arg_cpy)
{
	int	i;
	int	newline;
	int	changed;

	i = 1;
	newline = 0;
	changed = ft_strcmp_arg(argv, arg_cpy);
	while (argv[i] && valid_option(argv[i]))
	{
		newline = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (((!changed && !*arg_cpy[i]) || *argv[i])
			&& argv[i + 1] && *argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
