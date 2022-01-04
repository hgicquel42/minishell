/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:19:10 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/04 17:17:31 by hgicquel         ###   ########.fr       */
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

char	*ft_strdup(char *s)
{
	int		i;
	char	*r;

	r = malloc(l + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[l] = 0;
	return (r);
}
