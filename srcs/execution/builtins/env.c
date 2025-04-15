/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:05:03 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/17 09:45:27 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	not_valid_idenrifier(char *env, int export)
{
	if (export)
		ft_putstr_fd("minishell: export: `", 2);
	else
		ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(env, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	ft_env(char **argv, t_env *env)
{
	(void)env;
	if (argv[1] && !ft_strchr(argv[1], '='))
	{
		printf("env: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	print_env(env);
	if (argv[1] && ft_strchr(argv[1], '='))
		printf("%s\n", argv[1]);
	return (0);
}
