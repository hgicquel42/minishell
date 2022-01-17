/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:45:37 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/17 17:58:23 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_atoi(char *s, int *r)
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
	if (!i)
		return (false);
	*r = x;
	return (true);
}

int	ft_exit(t_state *g, char **args, char **envp)
{
	(void)envp;
	printf("exit\n");
	g->exit = true;
	if (!args[1])
	{
		g->exitval = 0;
		return (0);
	}
	if (!ft_atoi(args[1], &g->exitval))
	{
		g->exitval = 2;
		printf("exit: %s: numeric argument required\n", args[1]);
		return (1);
	}
	if (args[2])
	{
		g->exitval = 1;
		printf("exit: too many arguments\n");
		return (1);
	}
	return (0);
}
