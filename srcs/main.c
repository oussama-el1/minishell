/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:08:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/28 18:00:30 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	bash_loop(t_env *env)
{
	t_token		*token;
	char		*line;
	char		*tmp;
	static int	exit_status;

	setup_signals();
	while (YASSINE)
	{
		init_token(&token, 1);
		line = readline("minishell$> ");
		if (!line)
			return (perror("readline error!"));
		if (empty(line))
		{
			free(line);
			continue ;
		}
		tmp = ft_strdup(line);
		free(line);
		process_input(tmp, &token);
		execute_ast(build_ast(token), env, &exit_status);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)ac;
	(void)av;
	env = init_env(envp);
	bash_loop(env);
	return (0);
}
