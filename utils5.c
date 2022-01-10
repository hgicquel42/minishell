/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:58:31 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/10 16:31:09 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_free(void *p)
{
	if (p)
		free(p);
	return (0);
}

int	ft_freep(void **p)
{
	int	i;

	if (!p)
		return (0);
	i = 0 ;
	while (p[i])
		free(p[i++]);
	free(p);
	return (0);
}

int	ft_freel(void **p, int l)
{
	int	i;

	if (!p)
		return (0);
	i = 0 ;
	while (i < l)
		free(p[i++]);
	free(p);
	return (0);
}
