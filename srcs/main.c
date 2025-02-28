/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:08:50 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/02/28 12:58:46 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	bash_loop(void);

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	bash_loop();
	return (0);
}

static void	bash_loop(void)
{
	t_token	*token;
	char	*line;
	char	*tmp;

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
	}
}
