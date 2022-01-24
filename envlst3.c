/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:00:37 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/24 13:52:36 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_env	**ft_findenv2(t_env **start, char *key)
{
	t_env	**curr;

	curr = start;
	while (*curr)
	{
		if (!ft_strcmp((*curr)->key, key))
			return (curr);
		curr = &(*curr)->next;
	}
	return (NULL);
}

void	ft_remenv2(t_env **envn)
{
	t_env	*tmp;

	tmp = (*envn)->next;
	ft_free((*envn)->key);
	ft_free((*envn)->val);
	ft_free(*envn);
	*envn = tmp;
}

bool	ft_remenv(t_env **start, char *key)
{
	t_env	**envn;

	envn = ft_findenv2(start, key);
	if (!envn)
		return (false);
	ft_remenv2(envn);
	return (true);
}

bool	ft_setenv(t_env **start, char *key, char *val)
{
	ft_remenv(start, key);
	if (!ft_addenv(start, key, val))
		return (false);
	return (true);
}
