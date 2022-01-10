/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:24:40 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/10 17:39:30 by hgicquel         ###   ########.fr       */
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
	printf("Not found\n");
	ft_freep((void *) paths);
	return (1);
}

int	ft_route(t_state *s, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args, cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		printf("%s\n", ft_getcwd());
	else if (!ft_strcmp(cmd->args[0], "cd"))
		chdir(cmd->args[1]);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		s->exit = true;
	else
		return (ft_exec(s, cmd));
	return (0);
}

pid_t	ft_run(t_state *s, t_cmd *cmd)
{
	pid_t	pid;

	cmd->envp = malloc(1 * sizeof(char *));
	cmd->envp[0] = NULL; // TODO: convert g->envlst to array
	pid = fork();
	if (pid)
		return (pid);
	if (cmd->fdi)
	{
		dup2(cmd->fdi[0], STDIN_FILENO);
		close(cmd->fdi[0]);
		close(cmd->fdi[1]);
	}
	if (cmd->fdo)
	{
		dup2(cmd->fdo[1], STDOUT_FILENO);
		close(cmd->fdo[0]);
		close(cmd->fdo[1]);
	}
	exit(ft_route(s, cmd));
}
