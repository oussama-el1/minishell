/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:08:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/16 12:08:20 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void setup_signals(void)
{
	struct termios term;
	
	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void shell_loop(t_env *env)
{
	char		*input;
	static int	exit_status;

	setup_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_printf("exit\n");
			exit(exit_status);
		}
		if (*input)
			add_history(input);
		// printf("test echo \n");
		test(env, &exit_status);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	shell_loop(env);
	return (0);
}
