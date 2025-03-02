/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:08:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/02 14:00:57 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	bash_loop(t_env *env)
{
	t_token		*token;
	t_tree		*ast;
	char		*line;
	char		*tmp;
	static int	exit_status;


	setup_signals();
	while (1)
	{
		init_token(&token, 1);
		line = readline("minishell$> ");
		if (!line)
		{
			ft_printf("exit\n");
			exit(exit_status);
		}

		if (empty(line))
		{
			free(line);
			continue ;
		}
		tmp = ft_strdup(line);
		free(line);
		if (!process_input(tmp, &token, &ast, 1))
			continue ;
		execute_ast(ast, env, &exit_status);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env			*env;

	(void)ac;
	(void)av;
	env = init_env(envp);
	bash_loop(env);
	return (0);
}
