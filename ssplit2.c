/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssplit2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:10:06 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/05 16:39:42 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_chrcpy(char *r, int i, char c)
{
	if (r)
		r[i] = c;
}

t_tuple	ft_ssplit2_squote(t_state *g, t_tuple t, char *s, char *r)
{
	(void)g;
	t.i++;
	while (s[t.i] && s[t.i] != '\'')
		ft_chrcpy(r, t.j++, s[t.i++]);
	t.i++;
	return (t);
}

t_tuple	ft_ssplit2_dquote(t_state *g, t_tuple t, char *s, char *r)
{
	t.i++;
	while (s[t.i] && s[t.i] != '"')
	{
		if (s[t.i] == '$')
			t = ft_ssplit2_dollar(g, t, s, r);
		else
			ft_chrcpy(r, t.j++, s[t.i++]);
	}
	t.i++;
	return (t);
}

t_tuple	ft_ssplit2(t_state *g, char *s, char *r, char c)
{
	t_tuple	t;

	t.i = 0;
	t.j = 0;
	while (s[t.i] && s[t.i] != c)
	{
		if (s[t.i] == '$')
			t = ft_ssplit2_dollar(g, t, s, r);
		if (s[t.i] == '"')
			t = ft_ssplit2_dquote(g, t, s, r);
		else if (s[t.i] == '\'')
			t = ft_ssplit2_squote(g, t, s, r);
		else
			ft_chrcpy(r, t.j++, s[t.i++]);
	}
	return (t);
}
