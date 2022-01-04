/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:32:17 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/04 14:19:05 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_exec(t_state *s, char **args)
{
	(void)s;
	(void)args;
	return (true);
}

bool	ft_route(t_state *s, char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args + 1));
	else if (!ft_strcmp(args[0], "pwd"))
		printf("%s\n", ft_getcwd());
	else if (!ft_strcmp(args[0], "cd"))
		chdir(args[1]);
	else if (!ft_strcmp(args[0], "exit"))
		s->exit = true;
	else
		return (ft_exec(s, args));
	return (true);
}

bool	ft_readline(t_state *s)
{
	char	*line;
	char	**args;

	line = readline("> ");
	if (!line)
		return (false);
	args = ft_split(line, ' ');
	if (!args)
		return (false);
	s->retval = ft_route(s, args);
	return (true);
}

int	main(void)
{
	t_state	state;

	state.exit = 0;
	while (!state.exit)
		if (!ft_readline(&state))
			return (1);
	return (0);
}
