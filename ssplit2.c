/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:10:06 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/04 16:03:33 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_noop(void *x, void *y)
{
	(void)x;
	(void)y;
}

int	ft_ssplit_count2(char *s, int *r, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '?')
			{
				i++;
				j++;
			}
			else
			{
				k = i;
				while (ft_isenvchr(s[i]))
					i++;
				(void)k;
				j += 5;
			}
		}
		else if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
			{
				if (s[i] == '$')
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

void	ft_ssplit_copy2(char *s, char *w, char c)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '?')
			{
				i++;
				w[j++] = '0';
			}
			else
			{
				k = i;
				while (ft_isenvchr(s[i]))
					i++;
				(void)k;
				l = 0;
				while (l < 5)
					w[j++] = "hello"[l++];
			}
		}
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
