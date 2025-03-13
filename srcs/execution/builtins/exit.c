/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:04:04 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/13 20:24:18 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_atoll(const char *str, int *error)
{
	int				i;
	unsigned long	result;
	int				sign;
	int				overflow;

	i = 0;
	sign = 1;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		overflow = ft_handle_overflow(result, (str[i] - '0'), sign);
		if (overflow != 1)
			return (*error = 1, overflow);
		result = (result * 10) + str[i] - '0';
		i++;
	}
	return (result * sign);
}

static void	ft_exit_error(char **argv, long long *exit_code)
{
	int	overflow_error;

	overflow_error = 0;
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	*exit_code = ft_atoll(argv[1], &overflow_error);
	if (overflow_error)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
}

int	ft_exit(char **argv)
{
	long long	exit_code;

	exit_code = g_exit_status;
	if (!argv)
		maroc(0, FULLFREE, 0);
	else if (argv[1])
	{
		ft_exit_error(argv, &exit_code);
		if (argv[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		exit_code = exit_code % 256;
	}
	unlink("/tmp/heredoc_tmp");
	exit(exit_code);
}
