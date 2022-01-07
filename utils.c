/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:29:17 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/07 15:55:32 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_free(void *p)
{
	if (p)
		free(p);
	return (0);
}

int	ft_freel(char **p, int l)
{
	int	i;

	i = 0 ;
	while (i < l)
		free(p[i++]);
	free(p);
	return (0);
}

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
