/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:24:40 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/05 18:25:51 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	**ft_paths(t_state *s)
{
	t_env	*pathn;

	pathn = ft_findenv(s->envlst, "PATH");
	if (pathn)
		return (ft_split(pathn->value, ':'));
	return (NULL);
}

int	ft_exec2(char *path, char **args, char **env)
{
	pid_t	pid;
	int		sts;

	pid = fork();
	if (pid == 0)
	{
		execve(path, args, env);
		_exit(127);
	}
	else
	{
		waitpid(pid, &sts, 0);
		return (sts);
	}
}

int	ft_exec(t_state *s, char **args)
{
	char	*path;
	char	**paths;
	char	**env;
	int		sts;

	env = malloc(1 * sizeof(char *));
	env[0] = NULL;
	paths = ft_paths(s);
	sts = ft_exec2(args[0], args, env);
	if (WEXITSTATUS(sts) != 127)
		return (sts);
	while (paths && *paths)
	{
		path = ft_strjoin3(*paths, "/", args[0]); // TODO: free 
		sts = ft_exec2(path, args, env);
		if (WEXITSTATUS(sts) != 127)
			return (sts);
		paths++;
	}
	printf("Not found\n");
	return (sts);
}
