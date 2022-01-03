/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:10:06 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/03 17:13:42 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_split_count(char *s, int *r, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] != '"')
		{
			i++;
			j++;
		}
		else
		{
			i++;
			while (s[i] && s[i] != '"')
			{
				i++;
				j++;
			}
			i++;
		}
	}
	*r = i;
	return (j);
}

void	ft_split_copy(char *s, char *w, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] != '"')
			w[j++] = s[i++];
		else
		{
			i++;
			while (s[i] && s[i] != '"')
				w[j++] = s[i++];
			i++;
		}
	}
}
