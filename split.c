/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:03:57 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/13 12:23:19 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_tuple	ft_split2(char *s, char c, char *r)
{
	t_tuple	t;

	t.i = 0;
	t.o = 0;
	while (s[t.i] && s[t.i] != c)
		ft_chrcpy(r, t.o++, s[t.i++]);
	if (r)
		r[t.o] = 0;
	return (t);
}

int	ft_split_loop(char *s, char c, char **p)
{
	t_tuple	t;
	int		l;
	char	*r;

	l = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		t = ft_split2(s, c, NULL);
		if (t.o && !p)
			l++;
		if (t.o && p)
		{
			r = malloc(t.o + 1);
			if (!r)
				return (l);
			t = ft_split2(s, c, r);
			p[l++] = r;
		}
		s += t.i;
	}
	if (p)
		p[l] = 0;
	return (l);
}

char	**ft_split(char *s, char c)
{
	int		l;
	int		m;
	char	**p;

	l = ft_split_loop(s, c, NULL);
	p = malloc((l + 1) * sizeof(char *));
	if (!p)
		return (0);
	m = ft_split_loop(s, c, p);
	if (l != m)
		return (NULL);
	return (p);
}
