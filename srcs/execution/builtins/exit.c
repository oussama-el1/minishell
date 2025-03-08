/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:04:04 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/08 13:59:03 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_numeric(const char *str)
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

static int	ft_handle_overflow(unsigned long nbr, int ndigit, int sign)
{
	if (sign == 1)
		if ((nbr >= 922337203685477580 && ndigit > 7)
			|| nbr > 922337203685477580)
			return (-1);
	if (sign == -1)
		if ((nbr >= 922337203685477580 && ndigit > 8)
			|| nbr > 922337203685477580)
			return (0);
	return (1);
}

int	ft_atoll(const char *str, int *error)
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


int	ft_exit(char **argv)
{
	long long	exit_code;
	int			overflow_error;

	exit_code = 0;
	overflow_error = 0;
	if (!argv)
	{
		ft_putstr_fd("exit\n", 2);
		maroc(0, FULLFREE, 0);
	}
	else
	{
		if (!is_numeric(argv[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		exit_code = ft_atoll(argv[1], &overflow_error);
		if (overflow_error)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
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
