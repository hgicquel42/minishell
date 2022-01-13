/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:32:17 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/13 14:53:16 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	sigint(int sig)
{
	if (sig != SIGINT)
		exit(1);
	ft_putchr(1, '\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_state	g;

	(void)argc;
	(void)argv;
	if (!ft_fillenv(&g.envlst, envp))
		return (1);
	g.exit = 0;
	g.retval = 0;
	while (g.exit == 0)
		if (!ft_loop(&g))
			return (1);
	ft_freeenv(g.envlst);
	return (g.exit);
}
