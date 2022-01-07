/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:58:31 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/07 16:58:34 by hgicquel         ###   ########.fr       */
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