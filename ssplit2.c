/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssplit2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:39:02 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/17 16:26:32 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_convert_val(int n, t_tuple *t, char *r)
{
	if (n >= 10)
	{
		ft_convert_val(n / 10, t, r);
		ft_convert_val(n % 10, t, r);
		return ;
	}
	ft_chrcpy(r, t->o++, n + '0');
}

t_tuple	ft_ssplit_dollar_ret(t_state *g, t_tuple t, char *s, char *r)
{
	(void)s;
	t.i++;
	ft_convert_val(g->retval % 255, &t, r);
	return (t);
}

t_tuple	ft_ssplit_dollar_env(t_state *g, t_tuple t, char *s, char *r)
{
	int		l;
	char	*d;
	t_env	*n;

	l = 0;
	while (ft_isenvchr(s[t.i + l]))
		l++;
	if (!l)
	{
		ft_chrcpy(r, t.o++, '$');
		return (t);
	}
	d = ft_strldup(s + t.i, l, ft_chrid);
	n = ft_findenv(g->envlst, d);
	t.i += l;
	if (n)
	{
		l = ft_strlen(n->val);
		if (r)
			ft_strlcpy(n->val, r + t.o, l, ft_chrid);
		t.o += l;
	}
	free(d);
	return (t);
}

t_tuple	ft_ssplit_dollar(t_state *g, t_tuple t, char *s, char *r)
{
	t.i++;
	if (s[t.i] == '?')
		return (ft_ssplit_dollar_ret(g, t, s, r));
	else if (s[t.i] >= '0' && s[t.i] <= '9')
	{
		t.i++;
		return (t);
	}
	else
		return (ft_ssplit_dollar_env(g, t, s, r));
}
