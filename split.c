/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:28:36 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/03 16:25:14 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	ft_count_quote(char *s, int *r)
{
	int	j;

	j = 0;
	while (s[j + 1] && s[j + 1] != '"')
		j++;
	*r = j + 2;
	return (j);
}

static int	ft_count_raw(char *s, int *r, char c)
{
	int	j;

	j = 0;
	while (s[j] && s[j] != c)
		j++;
	*r = j;
	return (j);
}

static int	ft_count(char *s, int *r, char c)
{
	if (*s == '"')
		return (ft_count_quote(s, r));
	else
		return (ft_count_raw(s, r, c));
}

static	int	ft_split_count(char *s, char c)
{
	int	r;
	int	l;

	l = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (ft_count(s, &r, c))
			l++;
		s += r;
	}
	return (l);
}

static	int	ft_split_free(char **r, int k)
{
	int	i;

	i = 0 ;
	while (i < k)
		free(r[i++]);
	free(r);
	return (0);
}

static	int	ft_split_alloc(char *s, char c, char **p)
{
	int	i;
	int	i2;
	int	j;
	int	k;
	int	r;
	char	*w;

	k = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		j = ft_count(s, &r, c);
		if (!j)
			continue ;
		w = malloc(j + 1);
		if (!w)
			return (ft_split_free(p, k));
		i = 0;
		i2 = 0;
		while (i < r)
		{
			if (s[i] != '"')
				w[i2++] = s[i];
			i++;
		}
		s += i;
		w[j] = 0;
		p[k++] = w;
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
	if (!ft_split_alloc(s, c, r))
		return (0);
	r[l] = 0;
	return (r);
}
