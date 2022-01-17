/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:35:40 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/17 18:32:47 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_echo2(char **args)
{
	int	i;

	i = 0;
	while (ft_strlen(args[i]))
		if ((i > 0 && !ft_putchr(1, ' ')) || !ft_putstr(1, args[i++]))
			return (false);
	return (true);
}

int	ft_echo(char **args)
{
	bool	result;

	if (args[1] && !ft_strcmp(args[1], "-n"))
		return (!ft_echo2(args + 2));
	result = ft_echo2(args + 1);
	ft_putchr(1, '\n');
	return (!result);
}
