/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:52:37 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/12 17:22:40 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_env(char **args, char **envp)
{
	(void)args;
	if (!envp)
		return (1);
	while (*envp)
		printf("%s\n", *envp++);
	return (0);
}

int	ft_unset(t_state *g, char **args, char **envp)
{
	int	i;

	(void)envp;
	i = 1;
	while (args[i])
		ft_remenv(&(g->envlst), args[i++]);
	return (0);
}
