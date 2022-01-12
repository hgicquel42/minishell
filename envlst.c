/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:46:59 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/12 17:21:53 by hgicquel         ###   ########.fr       */
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

t_env	*ft_genenv(char *key, char *val)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->val = val;
	node->next = NULL;
	return (node);
}

bool	ft_addenv(t_env **start, char *key, char *val)
{
	t_env	*node;
	t_env	**curr;

	node = ft_genenv(key, val);
	if (!node)
		return (false);
	curr = start;
	while (*curr)
		curr = &((*curr)->next);
	*curr = node;
	return (true);
}

bool	ft_addrawenv(t_env **start, char *env)
{
	char	**kv;
	bool	result;

	kv = ft_split(env, '=');
	if (!kv)
		return (false);
	result = ft_addenv(start, kv[0], kv[1]);
	ft_free(kv);
	return (result);
}

bool	ft_fillenv(t_env **start, char **envp)
{
	bool	error;

	*start = NULL;
	error = false;
	while (*envp && !error)
		error += !ft_addrawenv(start, *envp++);
	if (!error)
		return (true);
	if (*start)
		ft_freeenv(*start);
	return (false);
}
