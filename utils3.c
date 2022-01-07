/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:37:13 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/07 14:31:52 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_strcpy(char *s, char *r, char (*f)(char))
{
	int	i;

	i = 0;
	while (s[i])
	{
		r[i] = f(s[i]);
		i++;
	}
}

void	ft_strlcpy(char *s, char *r, int l, char (*f)(char))
{
	int	i;

	i = 0;
	while (s[i] && i < l)
	{
		r[i] = f(s[i]);
		i++;
	}
}

char	*ft_strdup(char *s, char (*f)(char))
{
	int		l;
	char	*r;

	l = ft_strlen(s);
	r = malloc(l + 1);
	if (!r)
		return (NULL);
	ft_strcpy(s, r, f);
	return (r);
}

char	*ft_strldup(char *s, int l, char (*f)(char))
{
	char	*r;

	r = malloc(l + 1);
	if (!r)
		return (NULL);
	ft_strlcpy(s, r, l, f);
	return (r);
}
