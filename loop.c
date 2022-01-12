/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:51:02 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/12 19:35:22 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
		{
			waitpid(d.cmds[i]->pid, &s, 0);
			ft_freep((void *) d.cmds[i]->args);
			ft_freep((void *) d.cmds[i]->envp);
		}
		if (s)
			r = s;
		i++;
	}
	g->retval = r;
	return (true);
}

bool	ft_runall(t_state *g, t_ldata d, int l)
{
	int		i;
	int		s;
	bool	p;

	i = 0;
	while (i < l)
	{
		p = 0;
		s = 0;
		if (d.cmds[i])
		{			
			while (!p && d.prts[i + s + 1] && d.cmds[i + s + 2])
			{
				if (!ft_route_cmd_io(d, i, &s, &p))
					return (false);
			}
				
			d.cmds[i]->pid = ft_run(g, d.cmds[i]);
			if (d.cmds[i]->fdi != -1)
				close(d.cmds[i]->fdi);
			if (d.cmds[i]->fdo != -1)
				close(d.cmds[i]->fdo);
			if (s)
				i += s;
		}
		i++;
	}
	return (true);
}

char	*ft_readline(t_state *g)
{
	char	*line;

	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
	if (g->retval)
		line = readline("\033[0;31m$>_\033[0m ");
	else
		line = readline("\033[0;32m$>_\033[0m ");
	add_history(line);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (line);
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
	ft_freel((void *) d.prts, l);
	ft_freel((void *) d.cmds, l);
	ft_free((void *) d.pipes);
	return (true);
}
