/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssplit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:10:06 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/10 14:10:10 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_tuple	ft_ssplit_squote(t_state *g, t_tuple t, char *s, char *r)
{
	(void)g;
	t.i++;
	while (s[t.i] && s[t.i] != '\'')
		ft_chrcpy(r, t.o++, s[t.i++]);
	t.i++;
	return (t);
}

t_tuple	ft_ssplit_dquote(t_state *g, t_tuple t, char *s, char *r)
{
	t.i++;
	while (s[t.i] && s[t.i] != '"')
	{
		if (s[t.i] == '$')
			t = ft_ssplit_dollar(g, t, s, r);
		else
			ft_chrcpy(r, t.o++, s[t.i++]);
	}
	t.i++;
	return (t);
}

t_tuple	ft_ssplit(t_state *g, char *s, char *r)
{
	t_tuple	t;

	t.i = 0;
	t.o = 0;
	while (s[t.i] && s[t.i] != ' ')
	{
		if (s[t.i] == '$')
			t = ft_ssplit_dollar(g, t, s, r);
		if (s[t.i] == '"')
			t = ft_ssplit_dquote(g, t, s, r);
		else if (s[t.i] == '\'')
			t = ft_ssplit_squote(g, t, s, r);
		else
			ft_chrcpy(r, t.o++, s[t.i++]);
	}
	if (r)
		r[t.o] = 0;
	return (t);
}
