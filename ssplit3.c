/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssplit3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:39:02 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/07 15:01:17 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_tuple	ft_ssplit2_dollar_ret(t_state *g, t_tuple t, char *s, char *r)
{
	(void)s;
	t.i++;
	if (g->retval)
		ft_chrcpy(r, t.o++, '1');
	else
		ft_chrcpy(r, t.o++, '0');
	return (t);
}

t_tuple	ft_ssplit2_dollar_env(t_state *g, t_tuple t, char *s, char *r)
{
	int		l;
	char	*d;
	char	*u;
	t_env	*n;

	l = 0;
	while (ft_isenvchr(s[t.i + l]))
		l++;
	d = ft_strldup(s + t.i, l, ft_chrup);
	n = ft_findenv(g->envlst, d);
	ft_free(d);
	t.i += l;
	if (n)
	{
		l = ft_strlen(n->value);
		if (r)
			ft_strlcpy(n->value, r + t.o, l, ft_chrid);
		t.o += l;
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
