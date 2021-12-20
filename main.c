/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:32:17 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/20 18:02:14 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

typedef struct s_state
{
	
}	t_state;

char	*ft_getcwd()
{
	char	r[FILENAME_MAX];

	return (getcwd(r, FILENAME_MAX));
}

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

int	main(void)
{
	t_state	state;
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, "pwd"))
			printf("%s\n", ft_getcwd());
		else if (!ft_strcmp(line, "cd"))
			chdir("");
	}
	return (0);
}
