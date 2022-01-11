/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:32:17 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/11 14:59:33 by hgicquel         ###   ########.fr       */
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

bool	ft_runall(t_state *g, char **cmds, int l)
{
	t_cmd	**cmds2;
	int		*fds;
	int		i;

	cmds2 = ft_convertall(g, cmds, l);
	if (!cmds2)
		return (false);
	fds = malloc((l * 2) * sizeof(int));
	if (!fds)
		return (false);
	i = 0;
	while (i < l)
	{
		if (cmds2[i])
		{
			if (cmds[i + 1] && !ft_strcmp(cmds[i + 1], "|") && cmds2[i + 2])
			{
				if (pipe(fds + (i * 2)) == -1)
					return (false);
				cmds2[i]->fdo = fds + (i * 2);
				cmds2[i + 2]->fdi = fds + (i * 2);
			}
			if (cmds[i + 1] && !ft_strcmp(cmds[i + 1], ">") && cmds2[i + 2])
			{
				printf("redirection\n");
			}
			cmds2[i]->pid = ft_run(g, cmds2[i]);
			if (cmds2[i]->fdi)
				close(cmds2[i]->fdi[0]);
			if (cmds2[i]->fdo)
				close(cmds2[i]->fdo[1]);
		}
		i++;
	}
	i = 0;
	while (i < l)
	{
		if (cmds2[i])
			waitpid(cmds2[i]->pid, NULL, 0);
		i++;
	}
	ft_freep((void *) cmds);
	ft_freep((void *) cmds2);
	ft_free((void *) fds);
	return (true);
}

bool	ft_readline(t_state *g)
{
	char	*line;
	char	**cmds;
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
	return (ft_runall(g, cmds, l));
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
