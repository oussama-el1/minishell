/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:08:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/08 02:56:11 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)ac;
	(void)av;
	env = init_env(envp);
	bash_loop(&env);
	return (0);
}

static void	bash_loop(t_env **env)
{
	t_token		*token;
	static int	exit_status;
	t_helper	*hp;

	setup_signals();
	init_setup(&hp, &exit_status, env);
	while (1)
	{
		init_token(&token, 1);
		if (!get_exec_cmd(&token, hp))
			continue ;
		maroc(0, FREE, CMD);
	}
}

static int	get_exec_cmd(t_token **token, t_helper*helper)
{
	char	*line;
	char	*tmp;

	line = readline("minishell$> ");
	if (!line)
		ft_exit(NULL);
	if (empty(line))
		return (free(line), 0);
	tmp = ft_strdup(line, CMD);
	free(line);
	if (!process_input(tmp, token, helper, 1))
		return (maroc(0, FREE, CMD), 0);
	return (1);
}
