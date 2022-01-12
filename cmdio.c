/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 19:10:03 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/12 19:16:10 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_route_cmd_pipe(t_ldata d, int i, bool *s)
{
	(void)s;
	if (pipe(d.pipes + (i * 2)) == -1)
		return (false);
	d.cmds[i]->fdo = (d.pipes + (i * 2))[1];
	d.cmds[i + 2]->fdi = (d.pipes + (i * 2))[0];
	return (true);
}

bool	ft_route_cmd_dlbrackets(t_ldata d, int i, bool *s)
{
	(void)s;
	d.cmds[i]->fdo = open(d.cmds[i + 2]->args[0],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	*s = true;
	return (true);
}

bool	ft_route_cmd_drbrackets(t_ldata d, int i, bool *s)
{
	int		fdo;
	char	*line;

	if (pipe(d.pipes + (i * 2)) == -1)
		return (false);
	fdo = (d.pipes + (i * 2))[1];
	d.cmds[i]->fdi = (d.pipes + (i * 2))[0];
	while (1)
	{
		line = readline("> ");
		if (!line[0])
			break ;
		if (!ft_strcmp(line, d.prts[i + 2]))
			break ;
		if (!ft_putstr(fdo, line))
			break ;
		if (!ft_putchr(fdo, '\n'))
			break ;
	}
	close(fdo);
	*s = true;
	return (true);
}

bool	ft_route_cmd_io(t_ldata d, int i, bool *s)
{
	if (!ft_strcmp(d.prts[i + 1], "|"))
		return (ft_route_cmd_pipe(d, i, s));
	if (!ft_strcmp(d.prts[i + 1], ">>"))
		return (ft_route_cmd_dlbrackets(d, i, s));
	if (!ft_strcmp(d.prts[i + 1], "<<"))
		return (ft_route_cmd_drbrackets(d, i, s));
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
