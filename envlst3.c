/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:00:37 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/12 17:23:17 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_remenv(t_env **start, char *key)
{
	t_env	**curr;

	curr = start;
	while (*curr)
	{
		if (!ft_strcmp((*curr)->key, key))
			*curr = (*curr)->next;
		else
			curr = &(*curr)->next;
	}
}

bool	ft_setenv(t_env **start, char *key, char *val)
{
	ft_remenv(start, key);
	if (!ft_addenv(start, key, val))
		return (false);
	return (true);
}
