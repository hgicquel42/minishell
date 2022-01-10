/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:32:17 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/10 17:42:10 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_cmd	*ft_convert(t_state *g, char *cmd)
{
	t_cmd	*r;

	r = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	r->args = ft_xsplit(g, cmd, ft_ssplit);
	if (!r->args)
		return (NULL);
	r->envp = NULL;
	r->pid = 0;
	r->fdi = NULL;
	r->fdo = NULL;
	return (r);
}

t_cmd	**ft_convertall(t_state *g, char **cmds, int l)
{
	int		i;
	t_cmd	*r;
	t_cmd	**p;

	p = malloc((l + 1) * sizeof(t_cmd *));
	if (!p)
		return (NULL);
	i = 0;
	while (cmds[i])
	{
		if (!ft_strcmp(cmds[i], "|"))
			p[i++] = NULL;
		else
		{
			r = ft_convert(g, cmds[i]);
			if (!r)
				return (NULL);
			p[i++] = r;
		}
	}
	p[i] = NULL;
	return (p);
}

bool	ft_readline(t_state *g)
{
	char	*line;
	char	**cmds;
	t_cmd	**cmds2;
	int		fd[2];
	int		i;
	int		l;

	line = readline("> ");
	if (!line)
		return (false);
	cmds = ft_xsplit(g, line, ft_psplit);
	if (!cmds)
		return (false);
	l = 0;
	while (cmds[l])
		l++;
	cmds2 = ft_convertall(g, cmds, l);
	if (!cmds2)
		return (false);
	i = 0;
	while (i < l)
	{
		if (cmds2[i])
		{
			if (cmds[i + 1] && !ft_strcmp(cmds[i + 1], "|") && cmds2[i + 2])
			{
				pipe(fd);
				cmds2[i]->fdo = fd;
				cmds2[i + 2]->fdi = fd;
			}
			cmds2[i]->pid = ft_run(g, cmds2[i]);
		}
		i++;
	}
	i = 0;
	while (i < l)
	{
		if (cmds2[i])
		{
			waitpid(cmds2[i]->pid, NULL, 0);
			if (cmds[i + 1] && !ft_strcmp(cmds[i + 1], "|") && cmds2[i + 2])
			{
				close(cmds2[i]->fdo[0]);
				close(cmds2[i]->fdo[1]);
				close(cmds2[i + 2]->fdi[0]);
				close(cmds2[i + 2]->fdi[1]);
			}
		}
		i++;
	}
	ft_freep((void *) cmds);
	ft_freep((void *) cmds2);
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
