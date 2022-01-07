/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:03:57 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/07 14:59:29 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_split_count(char *s, char c)
{
	size_t	j;
	size_t	l;

	l = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		j = 0;
		while (s[j] && s[j] != c)
			j++;
		if (j)
			l++;
		s += j;
	}
	return (l);
}

int	ft_split_copy(char *s, char c, char **r)
{
	size_t	j;
	size_t	k;
	char	*w;

	k = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		j = 0;
		while (s[j] && s[j] != c)
			j++;
		if (!j)
			continue ;
		w = malloc(j + 1);
		if (!w)
			return (ft_freel(r, k));
		j = 0;
		while (*s && *s != c)
			w[j++] = *(s++);
		w[j] = 0;
		r[k++] = w;
	}
	return (1);
}

char	**ft_split(char *s, char c)
{
	int		l;
	char	**r;

	l = ft_split_count(s, c);
	r = malloc((l + 1) * sizeof(char *));
	if (!r)
		return (0);
	if (!ft_split_copy(s, c, r))
		return (0);
	r[l] = 0;
	return (r);
}
