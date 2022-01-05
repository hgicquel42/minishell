/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssplit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:28:36 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/05 15:59:41 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_ssplit_count(t_state *state, char *s, char c)
{
	t_tuple	t;
	int		l;

	l = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		t = ft_ssplit2(state, s, NULL, c);
		if (t.j)
			l++;
		s += t.i;
	}
	return (l);
}

bool	ft_ssplit_copy(t_state *g, char *s, char c, char **p)
{
	t_tuple	t;
	int		k;
	char	*r;

	k = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		t = ft_ssplit2(g, s, NULL, c);
		if (!t.j)
			continue ;
		r = malloc(t.j + 1);
		if (!r)
			return (ft_split_free(p, k));
		ft_ssplit2(g, s, r, c);
		s += t.i;
		r[t.j] = 0;
		p[k++] = r;
	}
	return (true);
}

char	**ft_ssplit(t_state *state, char *s, char c)
{
	int		l;
	char	**r;

	l = ft_ssplit_count(state, s, c);
	r = malloc((l + 1) * sizeof(char *));
	if (!r)
		return (0);
	if (!ft_ssplit_copy(state, s, c, r))
		return (0);
	r[l] = 0;
	return (r);
}
