/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:32:17 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/07 18:40:42 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_route(t_state *s, char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (!ft_echo(args + 1));
	else if (!ft_strcmp(args[0], "pwd"))
		printf("%s\n", ft_getcwd());
	else if (!ft_strcmp(args[0], "cd"))
		chdir(args[1]);
	else if (!ft_strcmp(args[0], "exit"))
		s->exit = true;
	else
		return (ft_exec(s, args));
	return (0);
}

bool	ft_readline(t_state *s)
{
	char	*line;
	char	**args;

	line = readline("> ");
	if (!line)
		return (false);
	args = ft_ssplit(s, line);
	if (!args)
		return (false);
	if (!args[0])
		return (true);
	s->retval = ft_route(s, args);
	ft_freep(args);
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_state	state;

	(void)argc;
	(void)argv;
	if (!ft_fillenv(&state.envlst, envp))
		return (1);
	state.exit = 0;
	while (!state.exit)
		if (!ft_readline(&state))
			return (1);
	return (0);
}
