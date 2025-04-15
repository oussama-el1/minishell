/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:31:02 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/17 09:04:51 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signals	g_signals = {0, 0, 0};

void	sigint_not_end(int sig)
{
	(void)sig;
	g_signals.sigint_child = 1;
	g_signals.exit_status = CTRL_C;
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
		g_signals.exit_status = CTRL_C;
		nb_lines(1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	setup_signals(t_helper *hp)
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
		return (1);
	}
	ft_putstr_fd("minishell: stdin is not a tty\n", STDERR_FILENO);
	g_signals.exit_status = 1;
	return (0);
}
