/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:51:34 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/19 16:03:54 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_stristoken(char	*s)
{
	if (!ft_strcmp(s, "|"))
		return (true);
	if (!ft_strcmp(s, ">"))
		return (true);
	if (!ft_strcmp(s, ">>"))
		return (true);
	if (!ft_strcmp(s, "<"))
		return (true);
	if (!ft_strcmp(s, "<<"))
		return (true);
	return (false);
}

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
	r->sts = 0;
	return (r);
}

t_cmd	**ft_convertall(t_state *g, char **prts, int l)
{
	int		i;
	t_cmd	*r;
	t_cmd	**p;

	p = malloc((l + 1) * sizeof(t_cmd *));
	if (!p)
		return (NULL);
	i = 0;
	while (prts[i])
	{
		if (ft_stristoken(prts[i]))
		{
			p[i++] = NULL;
			continue ;
		}
		r = ft_convert(g, prts[i]);
		if (!r)
			return (NULL);
		p[i++] = r;
	}
	p[i] = NULL;
	return (p);
}
