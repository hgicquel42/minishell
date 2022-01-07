/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssplit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:28:36 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/07 18:39:09 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_ssplit_loop(t_state *g, char *s, char **p)
{
	t_tuple	t;
	int		l;
	char	*r;

	l = 0;
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		t = ft_ssplit2(g, s, NULL);
		if (t.o && !p)
			l++;
		if (t.o && p)
		{
			r = malloc(t.o + 1);
			if (!r)
				return (l);
			t = ft_ssplit2(g, s, r);
			p[l++] = r;
		}
		s += t.i;
	}
	if (p)
		p[l] = 0;
	return (l);
}

char	**ft_ssplit(t_state *g, char *s)
{
	int		l;
	int		m;
	char	**p;

	l = ft_ssplit_loop(g, s, NULL);
	p = malloc((l + 1) * sizeof(char *));
	if (!p)
		return (0);
	m = ft_ssplit_loop(g, s, p);
	if (l != m)
	{
		ft_freel(p, m);
		return (NULL);
	}
	return (p);
}
