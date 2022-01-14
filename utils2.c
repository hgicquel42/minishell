/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:19:10 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/14 14:09:31 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_pwd(void)
{
	char	r[FILENAME_MAX];

	if (!getcwd(r, FILENAME_MAX))
		return (1);
	printf("%s\n", r);
	return (0);
}

char	*ft_strjoin2(char *a, char *b)
{
	int		i;
	size_t	la;
	size_t	lb;
	char	*p;

	la = ft_strlen(a);
	lb = ft_strlen(b);
	p = malloc(la + lb + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (*a)
		p[i++] = *a++;
	while (*b)
		p[i++] = *b++;
	p[i] = 0;
	return (p);
}

char	*ft_strjoin3(char *a, char *b, char *c)
{
	char	*ab;
	char	*abc;

	ab = ft_strjoin2(a, b);
	abc = ft_strjoin2(ab, c);
	free(ab);
	return (abc);
}
