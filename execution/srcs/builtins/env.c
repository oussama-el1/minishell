/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:05:03 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/04 15:15:34 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(char **argv, t_env *env)
{
	(void)env;
	if (argv[1] && !ft_strchr(argv[1], '='))
	{
		ft_printf("env: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	print_env(env);
	if (argv[1] && ft_strchr(argv[1], '='))
		ft_printf("%s\n", argv[1]);
	return (0);
}
