/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:08:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/17 00:25:37 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_exec_cmd(t_token **token, t_helper*helper);
static void	bash_loop(t_env **env);

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	((void)ac, (void)av);
	env = init_env(envp);
	bash_loop(&env);
	return (g_signals.exit_status);
}

static void	bash_loop(t_env **env)
{
	t_token		*token;
	t_helper	hp;

	if (!isatty(STDIN_FILENO))
    {
        ft_putendl_fd("Error: minishell must be run in an interactive terminal.", 2);
		g_signals.exit_status = 1;
		return ;
    }
	init_setup(&hp, env);
	setup_signals(&hp);
	while (1)
	{
		init_token(&token, 1);
		parse_exec_cmd(&token, &hp);
		fdmaroc(NULL, 0, CLEAR, 0);
		maroc(0, FREE, CMD);
	}
}

static void	parse_exec_cmd(t_token **token, t_helper *hp)
{
	char	*line;
	char	*tmp;

	hp->line_count++;
	line = readline("minishell$> ");
	if (!line)
		ft_exit(NULL);
	if (empty(line))
		return (free(line), (void)0);
	tmp = ft_strdup(line, CMD);
	free(line);
	process_input(tmp, token, hp, 1);
}
