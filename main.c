/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:32:17 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/11 16:13:35 by hgicquel         ###   ########.fr       */
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
	r->fdi = -1;
	r->fdo = -1;
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
		else if (!ft_strcmp(cmds[i], ">"))
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
	int		*pipes;
	bool	bracket;
	int		i;

	cmds2 = ft_convertall(g, cmds, l);
	if (!cmds2)
		return (false);
	pipes = malloc((l * 2) * sizeof(int));
	if (!pipes)
		return (false);
	i = 0;
	bracket = false;
	while (i < l)
	{
		if (cmds2[i] && bracket)
			bracket = false;
		else if (cmds2[i])
		{
			if (cmds[i + 1] && !ft_strcmp(cmds[i + 1], "|") && cmds2[i + 2])
			{
				if (pipe(pipes + (i * 2)) == -1)
					return (false);
				cmds2[i]->fdo = (pipes + (i * 2))[1];
				cmds2[i + 2]->fdi = (pipes + (i * 2))[0];
			}
			if (cmds[i + 1] && !ft_strcmp(cmds[i + 1], ">") && cmds2[i + 2])
			{
				cmds2[i]->fdo = open(cmds2[i + 2]->args[0], O_WRONLY | O_CREAT, 0644);
				bracket = true;
			}
			cmds2[i]->pid = ft_run(g, cmds2[i]);
			if (cmds2[i]->fdi != -1)
				close(cmds2[i]->fdi);
			if (cmds2[i]->fdo != -1)
				close(cmds2[i]->fdo);
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
	ft_free((void *) pipes);
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
