/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:46:59 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/04 16:16:13 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_env	*ft_genenv(char *env)
{
	t_env	*node;
	char	**kv;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	kv = ft_split(env, '=');
	node->key = kv[0];
	node->value = kv[1];
	node->next = NULL;
	return (node);
}

t_env	*ft_addenv(t_env *end, char *env)
{
	t_env	*node;

	(void)end;
	node = ft_genenv(env);
	printf("%s == %s\n", node->key, node->value);
	return (NULL);
}

t_env	*ft_envlst(char **envp)
{
	t_env	*start;

	start = NULL;
	while (*envp)
		ft_addenv(start, *envp++);
	return (start);
}
