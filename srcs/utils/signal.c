/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:31:02 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/16 23:52:21 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signals	g_signals = {0, 0, 0};

void	sigint_not_end(int sig)
{
	(void)sig;
	g_signals.sigint_child = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	signint_helper(t_helper *hp)
{
	g_signals.exit_status = g_signals.sigint_child;
	g_signals.sigint_child = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &hp->term);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signals.exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals(t_helper *hp)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		hp->term = term;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
