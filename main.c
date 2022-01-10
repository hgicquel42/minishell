/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:32:17 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/10 14:34:30 by hgicquel         ###   ########.fr       */
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

bool	ft_readcmd(t_state *g, char *cmd)
{
	char	**args;

	if (cmd[0] == '|')
		return (true);
	args = ft_xsplit(g, cmd, ft_ssplit);
	if (!args)
		return (false);
	if (args[0])
		g->retval = ft_route(g, args);
	ft_freep(args);
	return (true);
}

bool	ft_readline(t_state *g)
{
	char	*line;
	char	**cmds;
	int		i;

	line = readline("> ");
	if (!line)
		return (false);
	cmds = ft_xsplit(g, line, ft_psplit);
	if (!cmds)
		return (false);
	i = 0;
	while (cmds[i])
		if (!ft_readcmd(g, cmds[i++]))
			return (ft_freep(cmds) + false);
	ft_freep(cmds);
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
