/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:29:17 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/24 13:30:47 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

size_t	ft_ptrlen(void **p)
{
	size_t	l;

	l = 0;
	while (p && p[l])
		l++;
	return (l);
}

size_t	ft_strlen(char *s)
{
	size_t	l;

	l = 0;
	while (s && s[l])
		l++;
	return (l);
}

bool	ft_putchr(int fd, char c)
{
	return (write(fd, &c, 1) == 1);
}

bool	ft_putstr(int fd, char *s)
{
	ssize_t	l;

	l = (ssize_t) ft_strlen(s);
	return (write(fd, s, l) == l);
}
