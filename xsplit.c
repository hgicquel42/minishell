/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xsplit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:28:36 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/19 15:06:22 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_chrcpy(char *r, int i, char c)
{
	if (r)
		r[i] = c;
}

int	ft_xsplit_loop(
	t_state *g, char *s, char **p,
	t_tuple (*f)(t_state *g, char *s, char *r)
)
{
	t_tuple	t;
	int		l;
	char	*r;

	l = 0;
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		t = f(g, s, NULL);
		if (!p && t.i)
			l++;
		if (p && t.i)
		{
			r = malloc(t.o + 1);
			if (!r)
				return (l);
			t = f(g, s, r);
			p[l++] = r;
		}
		s += t.i;
	}
	if (p)
		p[l] = 0;
	return (l);
}

char	**ft_xsplit_empty(void)
{
	char	**p;
	char	*r;

	p = malloc(2);
	if (!p)
		return (NULL);
	r = malloc(1);
	if (!r)
		return (NULL);
	r[0] = 0;
	p[0] = r;
	p[1] = 0;
	return (p);
}

char	**ft_xsplit(
	t_state *g, char *s,
	t_tuple (*f)(t_state *g, char *s, char *r)
)
{
	int		l;
	int		m;
	char	**p;

	l = ft_xsplit_loop(g, s, NULL, f);
	p = malloc((l + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	m = ft_xsplit_loop(g, s, p, f);
	if (l != m)
		return (NULL);
	return (p);
}
