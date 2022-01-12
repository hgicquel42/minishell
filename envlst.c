/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:46:59 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/12 15:12:07 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_freeenv(t_env *envn)
{
	if (envn->next)
		ft_freeenv(envn->next);
	free(envn->key);
	free(envn->val);
	free(envn);
}

t_env	*ft_genenv(char *env)
{
	t_env	*node;
	char	**kv;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	kv = ft_split(env, '=');
	node->key = kv[0];
	node->val = kv[1];
	ft_free(kv);
	node->next = NULL;
	return (node);
}

bool	ft_addenv(t_env **start, char *env)
{
	t_env	*node;
	t_env	**curr;

	node = ft_genenv(env);
	if (!node)
		return (false);
	curr = start;
	while (*curr)
		curr = &((*curr)->next);
	*curr = node;
	return (true);
}

bool	ft_fillenv(t_env **start, char **envp)
{
	bool	error;

	*start = NULL;
	error = false;
	while (*envp && !error)
		error += !ft_addenv(start, *envp++);
	if (!error)
		return (true);
	if (*start)
		ft_freeenv(*start);
	return (false);
}
