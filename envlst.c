/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:46:59 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/04 15:56:28 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_env	*ft_genenv(char **envp)
{
	t_env	*start;

	start = NULL;
	while (*envp)
		printf("%s\n", *envp++);
	return (start);
}

// t_env	ft_addback(t_env *end, char	*k, char *v)
// {
// 	return (NULL);
// }