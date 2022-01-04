/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:10:06 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/04 14:39:09 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_noop(int i, int j)
{
	(void)i;
	(void)j;
}

int	ft_split_count(char *s, int *r, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i])
			{
				if (s[i] == '"')
					break ;
				else if (s[i] == '$')
				{
					
				}
				else
				{
					i++;
					j++;
				}
				
			}
			i++;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
			{
				i++;
				j++;
			}
			i++;
		}
		else
		{
			i++;
			j++;
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
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				w[j++] = s[i++];
			i++;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				w[j++] = s[i++];
			i++;
		}
		else
			w[j++] = s[i++];
	}
}
