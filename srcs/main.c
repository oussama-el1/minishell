/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:08:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/03 21:49:16 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	bash_loop(char **env);

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	bash_loop(env);
	return (0);
}

static void	bash_loop(char **env)
{
	t_env	*env_list;
	t_token	*token;
	char	*line;

	create_env_list(env_list, env);// still need to implement create_env_list
	while (1)
	{
		token = init_token();
		line = readline("minishell$> ");
		if (!line)
			exit_program();// still need to implement exit_program
		if (*line)
			add_history(line);
		if (only_spaces(line))
			free(line);
		else
			process_input(line, &token, env_list);
	}
}
