/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:45:37 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/13 14:59:16 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_atoi(char *s)
{
	int	i;
	int	x;
	int	n;

	n = 1;
	i = 0;
	while (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			n *= -1;
	x = 0;
	while (s[i] >= '0' && s[i] <= '9')
		x = (x * 10) + (n * (s[i++] - '0'));
	return (x);
}

int	ft_exit(t_state *g, char **args, char **envp)
{
	(void)args;
	(void)envp;
	if (args[1])
	{
		g->exit = ft_atoi(args[1]);
		return (0);
	}
	else
	{
		g->exit = 1;
		return (0);
	}
}
