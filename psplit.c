/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psplit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:03:14 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/12 13:20:17 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_tuple	ft_psplit_squote(t_state *g, t_tuple t, char *s, char *r)
{
	(void)g;
	t.i++;
	while (s[t.i] && s[t.i] != '\'')
		ft_chrcpy(r, t.o++, s[t.i++]);
	t.i++;
	return (t);
}

t_tuple	ft_psplit_dquote(t_state *g, t_tuple t, char *s, char *r)
{
	(void)g;
	t.i++;
	while (s[t.i] && s[t.i] != '"')
		ft_chrcpy(r, t.o++, s[t.i++]);
	t.i++;
	return (t);
}

t_tuple	ft_psplit_single(t_tuple t, char *s, char *r, bool *b)
{
	if (!t.o)
		ft_chrcpy(r, t.o++, s[t.i++]);
	*b = true;
	return (t);
}

t_tuple	ft_psplit_double(t_tuple t, char *s, char *r, bool *b)
{
	if (!t.o)
	{
		ft_chrcpy(r, t.o++, s[t.i++]);
		ft_chrcpy(r, t.o++, s[t.i++]);
	}
	*b = true;
	return (t);
}

t_tuple	ft_psplit(t_state *g, char *s, char *r)
{
	t_tuple	t;
	bool	b;

	b = 0;
	t.i = 0;
	t.o = 0;
	while (s[t.i] && !b)
	{
		if (s[t.i] == '>' && s[t.i + 1] == '>')
			t = ft_psplit_double(t, s, r, &b);
		else if (s[t.i] == '<' && s[t.i + 1] == '<')
			t = ft_psplit_double(t, s, r, &b);
		else if (s[t.i] == '|' || s[t.i] == '<' || s[t.i] == '>')
			t = ft_psplit_single(t, s, r, &b);
		else if (s[t.i] == '"')
			t = ft_psplit_dquote(g, t, s, r);
		else if (s[t.i] == '\'')
			t = ft_psplit_squote(g, t, s, r);
		else
			ft_chrcpy(r, t.o++, s[t.i++]);
	}
	if (r)
		r[t.o] = 0;
	return (t);
}
