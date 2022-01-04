/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:35:40 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/04 13:49:35 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_echo2(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		if ((i > 0 && !ft_putchr(' ')) || !ft_putstr(args[i++]))
			return (false);
	return (true);
}

bool	ft_echo(char **args)
{
	bool	result;

	if (!ft_strcmp(args[0], "-n"))
		return (ft_echo2(args + 1));
	result = ft_echo2(args);
	ft_putchr('\n');
	return (result);
}
