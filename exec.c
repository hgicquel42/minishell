/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:24:40 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/07 18:48:46 by hgicquel         ###   ########.fr       */
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
	int		i;
	char	**env;
	int		sts;

	env = malloc(1 * sizeof(char *));
	env[0] = NULL; // TODO
	sts = ft_exec2(args[0], args, env);
	if (WEXITSTATUS(sts) != 127)
		return (sts);
	paths = ft_paths(s);
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin3(*paths, "/", args[0]);
		sts = ft_exec2(path, args, env);
		ft_free(path);
		if (WEXITSTATUS(sts) != 127)
			return (ft_freep(paths) + sts);
		i++;
	}
	printf("Not found\n");
	ft_freep(paths);
	return (sts);
}
