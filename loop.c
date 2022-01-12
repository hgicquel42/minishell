/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:51:02 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/12 14:17:55 by hgicquel         ###   ########.fr       */
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

bool	ft_waitall(t_state *g, t_ldata d, int l)
{
	int	i;
	int	s;
	int	r;

	i = 0;
	r = 0;
	while (i < l)
	{
		if (d.cmds[i])
			waitpid(d.cmds[i]->pid, &s, 0);
		if (s)
			r = s;
		i++;
	}
	g->retval = r;
	return (true);
}

bool	ft_route_cmd_io(t_ldata d, int i, bool *s)
{
	if (!ft_strcmp(d.prts[i + 1], "|"))
	{
		if (pipe(d.pipes + (i * 2)) == -1)
			return (false);
		d.cmds[i]->fdo = (d.pipes + (i * 2))[1];
		d.cmds[i + 2]->fdi = (d.pipes + (i * 2))[0];
	}
	if (!ft_strcmp(d.prts[i + 1], ">>"))
	{
		d.cmds[i]->fdo = open(d.cmds[i + 2]->args[0],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		*s = true;
	}
	if (!ft_strcmp(d.prts[i + 1], ">"))
	{
		d.cmds[i]->fdo = open(d.cmds[i + 2]->args[0],
				O_WRONLY | O_CREAT, 0644);
		*s = true;
	}
	if (!ft_strcmp(d.prts[i + 1], "<"))
	{
		d.cmds[i]->fdi = open(d.cmds[i + 2]->args[0],
				O_RDONLY, 0644);
		*s = true;
	}
	return (true);
}

bool	ft_runall(t_state *g, t_ldata d, int l)
{
	int		i;
	bool	s;

	i = 0;
	while (i < l)
	{
		if (d.cmds[i])
		{
			if (d.prts[i + 1] && d.cmds[i + 2])
				if (!ft_route_cmd_io(d, i, &s))
					return (false);
			d.cmds[i]->pid = ft_run(g, d.cmds[i]);
			if (d.cmds[i]->fdi != -1)
				close(d.cmds[i]->fdi);
			if (d.cmds[i]->fdo != -1)
				close(d.cmds[i]->fdo);
			if (s)
				i++;
			s = false;
		}
		i++;
	}
	return (true);
}

bool	ft_init(t_state *g, t_ldata *d, char *line, int *rl)
{
	int	l;

	d->prts = ft_xsplit(g, line, ft_psplit);
	if (!d->prts)
		return (false);
	l = 0;
	while (d->prts[l])
		l++;
	d->cmds = ft_convertall(g, d->prts, l);
	if (!d->cmds)
		return (false);
	d->pipes = malloc((l * 2) * sizeof(int));
	if (!d->pipes)
		return (false);
	*rl = l;
	return (true);
}

bool	ft_loop(t_state *g)
{
	t_ldata	d;
	char	*line;
	int		l;

	line = ft_readline(g);
	if (!line)
		return (false);
	if (!ft_init(g, &d, line, &l))
		return (false);
	if (!ft_runall(g, d, l))
		return (false);
	if (!ft_waitall(g, d, l))
		return (false);
	ft_freep((void *) d.prts);
	ft_freep((void *) d.cmds);
	ft_free((void *) d.pipes);
	return (true);
}
