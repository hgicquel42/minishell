/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:52:04 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/17 18:38:55 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_env	*ft_findenv(t_env *start, char *key)
{
	t_env	*curr;

	curr = start;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	ft_envtostr3(t_env *envn, char *r)
{
	int	i;
	int	o;

	o = 0;
	i = 0;
	while (envn->key[i])
		ft_chrcpy(r, o++, envn->key[i++]);
	ft_chrcpy(r, o++, '=');
	i = 0;
	while (envn->val[i])
		ft_chrcpy(r, o++, envn->val[i++]);
	if (r)
		r[o] = 0;
	return (o);
}

int	ft_envtostr2(t_env *envn, char **p)
{
	int		l;
	int		o;
	char	*r;

	l = 0;
	while (envn)
	{
		o = ft_envtostr3(envn, NULL);
		if (p)
		{
			r = malloc(o + 1);
			if (!r)
				return (l);
			o = ft_envtostr3(envn, r);
			p[l] = r;
		}
		envn = envn->next;
		l++;
	}
	if (p)
		p[l] = 0;
	return (l);
}

char	**ft_envtostr(t_env *start)
{
	int		l;
	int		m;
	char	**p;

	l = ft_envtostr2(start, NULL);
	p = malloc((l + 1) * sizeof(char *));
	if (!p)
		return (0);
	m = ft_envtostr2(start, p);
	if (l != m)
		return (NULL);
	return (p);
}
