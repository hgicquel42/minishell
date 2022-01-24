/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:43:54 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/24 13:44:08 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_export2(t_state *g, char *arg)
{
	char	**kv;

	kv = ft_split(arg, '=');
	if (!kv[0])
	{
		printf("export: \"%s\": not a valid identifier\n", arg);
		ft_freep((void **) kv);
		return (1);
	}
	if (!ft_isenvstr(kv[0]))
	{
		printf("export: \"%s\": not a valid identifier\n", arg);
		ft_freep((void **) kv);
		return (1);
	}
	if (!kv[1])
		return (ft_freep((void **) kv));
	ft_setenv(&(g->envlst), kv[0], kv[1]);
	ft_free(kv);
	return (0);
}

int	ft_export3(char **envp)
{
	char	**kv;

	ft_sort(envp);
	while (*envp)
	{
		kv = ft_split(*envp++, '=');
		if (kv[0] && kv[1])
			printf("declare -x %s=\"%s\"\n", kv[0], kv[1]);
		ft_freep((void **) kv);
	}
	return (0);
}

int	ft_export(t_state *g, char **args, char **envp)
{
	int		i;
	bool	e;

	if (!ft_strlen(args[1]))
		return (ft_export3(envp));
	i = 1;
	e = false;
	while (args[i])
		e |= ft_export2(g, args[i++]);
	return (e);
}
