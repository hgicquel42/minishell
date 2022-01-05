/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssplit2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:10:06 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/05 16:31:02 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_chrcpy(char *r, int i, char c)
{
	if (r)
		r[i] = c;
}

t_tuple	ft_ssplit2_dollar_ret(t_state *g, t_tuple t, char *s, char *r)
{
	(void)s;
	t.i++;
	if (g->retval)
		ft_chrcpy(r, t.j++, '1');
	else
		ft_chrcpy(r, t.j++, '0');
	return (t);
}

t_tuple	ft_ssplit2_dollar_env(t_state *g, t_tuple t, char *s, char *r)
{
	int		l;
	char	*k;
	t_env	*n;

	l = 0;
	while (ft_isenvchr(s[t.i + l]))
		l++;
	k = ft_strldup(s + t.i, l);
	n = ft_findenv(g->envlst, k);
	t.i += l;
	if (n)
	{
		l = ft_strlen(n->value);
		if (r)
			ft_strlcpy(n->value, r + t.j, l);
		t.j += l;
	}
	return (t);
}

t_tuple	ft_ssplit2_dollar(t_state *g, t_tuple t, char *s, char *r)
{
	t.i++;
	if (s[t.i] == '?')
		return (ft_ssplit2_dollar_ret(g, t, s, r));
	else
		return (ft_ssplit2_dollar_env(g, t, s, r));
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
