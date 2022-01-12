/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:51:02 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/12 13:53:40 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_readline(t_state *g)
{
	char	*line;

	if (g->retval)
		line = readline("\033[0;31m$>_\033[0m ");
	else
		line = readline("\033[0;32m$>_\033[0m ");
	return (line);
}

bool	ft_waitall(t_state *g, t_cmd **cmds, int l)
{
	int	i;
	int	s;
	int	r;

	i = 0;
	r = 0;
	while (i < l)
	{
		if (cmds[i])
			waitpid(cmds[i]->pid, &s, 0);
		if (s)
			r = s;
		i++;
	}
	g->retval = r;
	return (true);
}

bool	ft_runall(t_state *g, char **prts, t_cmd **cmds, int l)
{
	int		*pipes;
	bool	ignore;
	int		i;

	pipes = malloc((l * 2) * sizeof(int));
	if (!pipes)
		return (false);
	i = 0;
	ignore = false;
	while (i < l)
	{
		if (cmds[i] && ignore)
			ignore = false;
		else if (cmds[i])
		{
			if (prts[i + 1] && !ft_strcmp(prts[i + 1], "|") && cmds[i + 2])
			{
				if (pipe(pipes + (i * 2)) == -1)
					return (false);
				cmds[i]->fdo = (pipes + (i * 2))[1];
				cmds[i + 2]->fdi = (pipes + (i * 2))[0];
			}
			if (prts[i + 1] && !ft_strcmp(prts[i + 1], ">>") && cmds[i + 2])
			{
				cmds[i]->fdo = open(cmds[i + 2]->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
				ignore = true;
			}
			if (prts[i + 1] && !ft_strcmp(prts[i + 1], ">") && cmds[i + 2])
			{
				cmds[i]->fdo = open(cmds[i + 2]->args[0], O_WRONLY | O_CREAT, 0644);
				ignore = true;
			}
			if (prts[i + 1] && !ft_strcmp(prts[i + 1], "<") && cmds[i + 2])
			{
				cmds[i]->fdi = open(cmds[i + 2]->args[0], O_RDONLY, 0644);
				ignore = true;
			}
			cmds[i]->pid = ft_run(g, cmds[i]);
			if (cmds[i]->fdi != -1)
				close(cmds[i]->fdi);
			if (cmds[i]->fdo != -1)
				close(cmds[i]->fdo);
		}
		i++;
	}
	ft_free((void *) pipes);
	return (true);
}

bool	ft_loop(t_state *g)
{
	char	*line;
	char	**prts;
	t_cmd	**cmds;
	int		l;

	line = ft_readline(g);
	if (!line)
		return (false);
	prts = ft_xsplit(g, line, ft_psplit);
	if (!prts)
		return (false);
	l = 0;
	while (prts[l])
		l++;
	cmds = ft_convertall(g, prts, l);
	if (!cmds)
		return (false);
	if (!ft_runall(g, prts, cmds, l))
		return (false);
	if (!ft_waitall(g, cmds, l))
		return (false);
	ft_freep((void *) prts);
	ft_freep((void *) cmds);
	return (true);
}
