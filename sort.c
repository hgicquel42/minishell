/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:48:43 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/19 16:30:13 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_sort(char **p)
{
	int		i;
	int		j;
	int		l;
	char	*t;

	l = ft_ptrlen((void **) p);
	i = 0;
	while (i < l)
	{
		j = i + 1;
		while (j < l)
		{
			if (ft_strcmp(p[i], p[j]) > 0)
			{
				t = p[i];
				p[i] = p[j];
				p[j] = t;
			}
			j++;
		}
		i++;
	}
}
