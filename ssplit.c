/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssplit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:28:36 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/04 16:04:03 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_ssplit_count(char *s, char c)
{
	int	r;
	int	l;

	l = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (ft_ssplit_count2(s, &r, c))
			l++;
		s += r;
	}
	return (l);
}

int	ft_ssplit_copy(char *s, char c, char **p)
{
	int		j;
	int		k;
	int		r;
	char	*w;

	k = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		j = ft_ssplit_count2(s, &r, c);
		if (!j)
			continue ;
		w = malloc(j + 1);
		if (!w)
			return (ft_split_free(p, k));
		ft_ssplit_copy2(s, w, c);
		s += r;
		w[j] = 0;
		p[k++] = w;
	}
	return (1);
}

char	**ft_ssplit(char *s, char c)
{
	int		l;
	char	**r;

	l = ft_ssplit_count(s, c);
	r = malloc((l + 1) * sizeof(char *));
	if (!r)
		return (0);
	if (!ft_ssplit_copy(s, c, r))
		return (0);
	r[l] = 0;
	return (r);
}
