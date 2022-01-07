/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:37:13 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/07 18:51:35 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_strcpy(char *s, char *r, char (*f)(char))
{
	int	i;

	i = 0;
	while (s[i])
	{
		r[i] = f(s[i]);
		i++;
	}
	return (i);
}

int	ft_strlcpy(char *s, char *r, int l, char (*f)(char))
{
	int	i;

	i = 0;
	while (s[i] && i < l)
	{
		r[i] = f(s[i]);
		i++;
	}
	return (i);
}

char	*ft_strdup(char *s, char (*f)(char))
{
	int		i;
	int		l;
	char	*r;

	l = ft_strlen(s);
	r = malloc(l + 1);
	if (!r)
		return (NULL);
	i = ft_strcpy(s, r, f);
	r[i] = 0;
	return (r);
}

char	*ft_strldup(char *s, int l, char (*f)(char))
{
	int		i;
	char	*r;

	r = malloc(l + 1);
	if (!r)
		return (NULL);
	i = ft_strlcpy(s, r, l, f);
	r[i] = 0;
	return (r);
}
