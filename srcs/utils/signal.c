/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:31:02 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/15 07:54:15 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_received_signal = 0;

void	handle_sigint(int sig)
{
	static struct termios term;
	(void)sig;
	if (sig == SIGINT)
	{
		if (g_exit_status == SECOND)
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
		else
		{
			ft_putstr_fd("\n", 1);
			// Reset terminal attributes
			tcgetattr(STDIN_FILENO, &term);
			term.c_lflag &= ~ECHOCTL;
			tcsetattr(STDIN_FILENO, TCSANOW, &term);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		g_exit_status = 130;
	}
}

void	setup_signals(void)
{
	struct termios	term;

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
