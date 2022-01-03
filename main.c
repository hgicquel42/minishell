/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:32:17 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/03 16:12:44 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_readline(t_state *state)
{
	char	*line;
	char	**args;

(void)args;
	line = readline("> ");
	args = ft_split(line, ' ');
	// state->exit = 1;
	if (!ft_strcmp(args[0], "echo"))
		printf("%s\n", args[1]);
	else if (!ft_strcmp(args[0], "pwd"))
		printf("%s\n", ft_getcwd());
	else if (!ft_strcmp(args[0], "cd"))
		chdir("");
	else if (!ft_strcmp(args[0], "exit"))
		state->exit = 1;
	return (1);
}

int	main(void)
{
	t_state	state;

	state.exit = 0;
	while (!state.exit)
		if (!ft_readline(&state))
			return (1);
	return (0);
}
