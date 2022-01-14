/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:24:40 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/14 11:21:07 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	**ft_paths(t_state *s)
{
	t_env	*pathn;

	pathn = ft_findenv(s->envlst, "PATH");
	if (pathn)
		return (ft_split(pathn->val, ':'));
	return (NULL);
}

int	ft_exec(t_state *g, t_cmd *cmd)
{
	char	*path;
	char	**paths;
	int		i;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd->args[0], cmd->args, cmd->envp);
	paths = ft_paths(g);
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin3(paths[i], "/", cmd->args[0]);
		execve(path, cmd->args, cmd->envp);
		ft_free(path);
		i++;
	}
	printf("%s: command not found\n", cmd->args[0]);
	ft_freep((void **) paths);
	return (127);
}
