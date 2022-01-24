/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:30:48 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/24 13:32:35 by hgicquel         ###   ########.fr       */
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

int	ft_strlcmp(char *a, char *b, int l)
{
	int	i;

	i = 0;
	while (a[i] && a[i] == b[i] && i < l)
		i++;
	if (i == l)
		return (0);
	return (a[i] - b[i]);
}
