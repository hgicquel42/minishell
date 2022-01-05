/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:19:10 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/05 15:06:57 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_getcwd(void)
{
	char	r[FILENAME_MAX];

	return (getcwd(r, FILENAME_MAX));
}

bool	ft_isenvchr(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= 'a' && c <= 'z')
		return (true);
	return (c == '_');
}

bool	ft_toupperchr(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	return (c);
}

void	ft_strcpy(char *s, char *r)
{
	int	i;

	i = 0;
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
}

void	ft_strlcpy(char *s, char *r, int l)
{
	int	i;

	i = 0;
	while (s[i] && i < l)
	{
		r[i] = s[i];
		i++;
	}
}

char	*ft_strdup(char *s)
{
	int		l;
	char	*r;

	l = ft_strlen(s);
	r = malloc(l + 1);
	if (!r)
		return (NULL);
	ft_strcpy(s, r);
	return (r);
}

char	*ft_strldup(char *s, int l)
{
	char	*r;

	r = malloc(l + 1);
	if (!r)
		return (NULL);
	ft_strlcpy(s, r, l);
	return (r);
}
