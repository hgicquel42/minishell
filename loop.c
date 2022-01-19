/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:51:02 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/19 16:21:02 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_waitall(t_state *g, t_ldata d, int l)
{
	int	i;

	i = 0;
	g->retval = 0;
	while (i < l)
	{
		if (d.cmds[i])
		{
			if (d.cmds[i]->pid)
				waitpid(d.cmds[i]->pid, &(d.cmds[i]->sts), 0);
			if (d.cmds[i]->sts)
				g->retval = d.cmds[i]->sts;
			ft_freep((void **) d.cmds[i]->args);
			ft_freep((void **) d.cmds[i]->envp);
		}
		i++;
	}
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
			while (!p && d.prts[i + s + 1])
				if (!ft_route_cmd_io(d, i, &s, &p))
					return (true);
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
	if (g->retval)
		line = readline("\033[0;31m$>_\033[0m ");
	else
		line = readline("\033[0;32m$>_\033[0m ");
	add_history(line);
	signal(SIGINT, SIG_IGN);
	return (line);
}

bool	ft_init(t_state *g, t_ldata *d, char *line, int *rl)
{
	int	l;

	d->prts = ft_xsplit(g, line, ft_psplit);
	if (!d->prts)
		return (false);
	l = ft_ptrlen((void **) d->prts);
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
	{
		ft_putstr(1, "exit\n");
		g->exitval = 0;
		g->exit = true;
		return (true);
	}
	if (!ft_init(g, &d, line, &l))
		return (false);
	if (!ft_runall(g, d, l))
		return (false);
	if (!ft_waitall(g, d, l))
		return (false);
	ft_freel((void **) d.prts, l);
	ft_freel((void **) d.cmds, l);
	ft_free(d.pipes);
	ft_free(line);
	return (true);
}
