/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:03:00 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/17 09:46:11 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	ft_unset(char **argv, t_env **env)
{
	int	i;
	int	status;

	if (!argv[1])
		return (0);
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (validate_var_name(argv[i]))
			unset_env_var(env, argv[i]);
		else
		{
			not_valid_idenrifier(argv[i], 0);
			status = 1;
		}
		i++;
	}
	return (status);
}
