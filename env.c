/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:52:37 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/13 13:06:25 by hgicquel         ###   ########.fr       */
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

int	ft_export(t_state *g, char **args, char **envp)
{
	int		i;
	char	**kv;

	(void)envp;
	i = 1;
	while (args[i])
	{
		kv = ft_split(args[i++], '=');
		if (!kv[0] || !kv[1])
			return (1);
		if (!ft_isenvstr(kv[0]))
			return (1);
		ft_setenv(&(g->envlst), kv[0], kv[1]);
		ft_free(kv);
	}
	return (0);
}
