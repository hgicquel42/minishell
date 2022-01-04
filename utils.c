/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:29:17 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/04 15:26:01 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

bool	ft_putchr(char c)
{
	return (write(1, &c, 1) == 1);
}

size_t	ft_strlen(char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

bool	ft_putstr(char *s)
{
	ssize_t	l;

	l = (ssize_t) ft_strlen(s);
	return (write(1, s, l) == l);
}

char	*ft_strjoin2(char *a, char *b)
{
	int		i;
	size_t	la;
	size_t	lb;
	char	*p;

	la = ft_strlen(a);
	lb = ft_strlen(b);
	p = malloc(la + lb + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (*a)
		p[i++] = *a++;
	while (*b)
		p[i++] = *b++;
	p[i] = 0;
	return (p);
}
