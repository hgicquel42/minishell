/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:34:21 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/13 13:01:35 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	ft_chrid(char c)
{
	return (c);
}

char	ft_chrup(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	return (c);
}

bool	ft_isenvchr(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= 'a' && c <= 'z')
		return (true);
	if (c >= '0' && c <= '9')
		return (true);
	return (c == '_');
}

bool	ft_isenvstr(char *s)
{
	while (*s)
		if (!ft_isenvchr(*s++))
			return (false);
	return (true);
}
