/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:59:24 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/12 01:05:07 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	test_shell_restore(t_env *env)
{
	char *argv[] = {"man", "strlen", NULL};
	t_tree cmd1 = {CMD, argv, NULL, NULL, 0, NULL, NULL};
	return (exec_command(&cmd1, env));
}
