/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 19:10:03 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/13 13:36:26 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_route_cmd_pipe(t_ldata d, int i, bool *p)
{
	if (pipe(d.pipes + (i * 2)) == -1)
		return (false);
	d.cmds[i]->fdo = (d.pipes + (i * 2))[1];
	d.cmds[i + 2]->fdi = (d.pipes + (i * 2))[0];
	*p = true;
	return (true);
}

bool	ft_route_cmd_dlbrackets(t_ldata d, int i, int *s)
{
	char	*file;

	(void)s;
	file = d.cmds[i + *s + 2]->args[0];
	d.cmds[i]->fdo = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	*s += 2;
	return (true);
}

bool	ft_route_cmd_drbrackets(t_ldata d, int i, int *s)
{
	int		fdo;
	char	*word;
	char	*line;

	if (pipe(d.pipes + (i * 2)) == -1)
		return (false);
	fdo = (d.pipes + (i * 2))[1];
	d.cmds[i]->fdi = (d.pipes + (i * 2))[0];
	word = d.cmds[i + *s + 2]->args[0];
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, word))
			break ;
		if (!ft_putstr(fdo, line))
			break ;
		if (!ft_putchr(fdo, '\n'))
			break ;
	}
	close(fdo);
	*s += 2;
	return (true);
}

bool	ft_route_cmd_io(t_ldata d, int i, int *s, bool *p)
{
	char	*file;

	if (!ft_strcmp(d.prts[i + *s + 1], "|"))
		return (ft_route_cmd_pipe(d, i, p));
	else if (!ft_strcmp(d.prts[i + *s + 1], ">>"))
		return (ft_route_cmd_dlbrackets(d, i, s));
	else if (!ft_strcmp(d.prts[i + *s + 1], "<<"))
		return (ft_route_cmd_drbrackets(d, i, s));
	else if (!ft_strcmp(d.prts[i + *s + 1], ">"))
	{
		file = d.cmds[i + *s + 2]->args[0];
		d.cmds[i]->fdo = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		*s += 2;
	}
	else if (!ft_strcmp(d.prts[i + *s + 1], "<"))
	{
		file = d.cmds[i + *s + 2]->args[0];
		d.cmds[i]->fdi = open(file, O_RDONLY, 0644);
		*s += 2;
	}
	return (true);
}
