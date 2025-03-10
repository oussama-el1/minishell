/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:08:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/10 23:21:01 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_exec_cmd(t_token **token, t_helper*helper);
static void	bash_loop(t_env **env);

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
	t_helper	hp;

	init_setup(&hp, env);
	setup_signals();
	while (1)
	{
		init_token(&token, 1);
		get_exec_cmd(&token, &hp);
		maroc(0, FREE, CMD);
	}
}

static void	get_exec_cmd(t_token **token, t_helper*helper)
{
	char	*line;
	char	*tmp;

	g_signal_info.line_count++;
	line = readline("minishell$> ");
	if (!line)
		ft_exit(NULL);
	if (empty(line))
		return (free(line), (void)0);
	tmp = ft_strdup(line, CMD);
	free(line);
	process_input(tmp, token, helper, 1);
	g_signal_info.skip_herdoc = 0;
}
