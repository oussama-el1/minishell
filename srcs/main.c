/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:08:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/13 08:27:39 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	bash_loop(char **env);
int	g_exit_status = 0;


int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	bash_loop(env);
	return (0);
}

static void	bash_loop(char **env)
{
	t_env	*env_list;
	t_token	*token;
	char	*line;

	env_list = init_env(env);
	// print_export(env_list, 0);
	while (1)
	{
		token = init_token();
		line = readline("minishell$> ");
		if (!line)
			return ((void)ft_printf("readline error!\n"));
		if (*line)
			add_history(line);
		if (only_spaces(line))
			free(line);
		else
			process_input(line, &token, env_list);
	}
}
