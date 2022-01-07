/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssplit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:28:36 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/07 17:13:40 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_ssplit_count(t_state *state, char *s)
{
	t_tuple	t;
	int		l;

	l = 0;
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		t = ft_ssplit2(state, s, NULL);
		if (t.o)
			l++;
		s += t.i;
	}
	return (l);
}

bool	ft_ssplit_copy(t_state *g, char *s, char **p)
{
	t_tuple	t;
	int		k;
	char	*r;

	k = 0;
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		t = ft_ssplit2(g, s, NULL);
		if (!t.o)
			continue ;
		r = malloc(t.o + 1);
		if (!r)
			return (ft_freel(p, k));
		ft_ssplit2(g, s, r);
		s += t.i;
		r[t.o] = 0;
		p[k++] = r;
	}
	return (true);
}

char	**ft_ssplit(t_state *state, char *s)
{
	int		l;
	char	**r;

	l = ft_ssplit_count(state, s);
	r = malloc((l + 1) * sizeof(char *));
	if (!r)
		return (0);
	if (!ft_ssplit_copy(state, s, r))
		return (0);
	r[l] = 0;
	return (r);
}
