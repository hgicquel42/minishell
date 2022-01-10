/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:24:40 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/10 15:10:31 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_route(t_state *s, t_cmd cmd)
{
	char	**envp;

	envp = malloc(1 * sizeof(char *));
	envp[0] = NULL; // TODO: convert g->envlst to array
	if (!ft_strcmp(cmd.args[0], "echo"))
		return (ft_run(ft_echo, cmd));
	else if (!ft_strcmp(cmd.args[0], "pwd"))
		printf("%s\n", ft_getcwd());
	else if (!ft_strcmp(cmd.args[0], "cd"))
		chdir(cmd.args[1]);
	else if (!ft_strcmp(cmd.args[0], "exit"))
		s->exit = true;
	else
		return (ft_exec(s, cmd));
	return (0);
}

char	**ft_paths(t_state *s)
{
	t_env	*pathn;

	pathn = ft_findenv(s->envlst, "PATH");
	if (pathn)
		return (ft_split(pathn->val, ':'));
	return (NULL);
}

int	ft_run(int (*f(char	**args, char **envp)), t_cmd cmd)
{
	pid_t	pid;
	int		sts;

	pid = fork();
	if (pid == 0)
	{
		f(cmd.args, cmd.envp);
		_exit(127);
	}
	else
	{
		waitpid(pid, &sts, 0);
		return (sts);
	}
}

int	ft_exec2(char *path, t_cmd cmd)
{
	pid_t	pid;
	int		sts;

	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd.args, cmd.envp);
		_exit(127);
	}
	else
	{
		waitpid(pid, &sts, 0);
		return (sts);
	}
}

int	ft_exec(t_state *g, t_cmd cmd)
{
	char	*path;
	char	**paths;
	int		i;
	int		sts;

	sts = ft_exec2(cmd.args[0], cmd);
	if (WEXITSTATUS(sts) != 127)
		return (sts);
	paths = ft_paths(g);
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin3(paths[i], "/", cmd.args[0]);
		sts = ft_exec2(path, cmd);
		ft_free(path);
		if (WEXITSTATUS(sts) != 127)
			return (ft_freep(paths) + sts);
		i++;
	}
	printf("Not found\n");
	ft_freep(paths);
	return (sts);
}
