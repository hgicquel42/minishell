/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:24:40 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/13 13:06:09 by hgicquel         ###   ########.fr       */
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
	ft_putstr(1, "Not found\n");
	ft_freep((void *) paths);
	return (1);
}

int	ft_route_parent(t_state *g, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (chdir(cmd->args[1]) == -1);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(g, cmd->args, cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "export") && cmd->args[1])
		return (ft_export(g, cmd->args, cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		g->exit = true;
	else
		return (127);
	return (0);
}

int	ft_route_fork(t_state *s, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args, cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(cmd->args, cmd->envp));
	if (!ft_strcmp(cmd->args[0], "export") && !cmd->args[1])
		return (ft_env(cmd->args, cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		printf("%s\n", ft_getcwd());
	else
		return (ft_exec(s, cmd));
	return (0);
}

pid_t	ft_run(t_state *g, t_cmd *cmd)
{
	pid_t	pid;
	int		sts;

	sts = ft_route_parent(g, cmd);
	pid = fork();
	if (pid)
		return (pid);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd->envp = ft_envtostr(g->envlst);
	if (cmd->fdi != -1)
	{
		dup2(cmd->fdi, STDIN_FILENO);
		close(cmd->fdi);
	}
	if (cmd->fdo != -1)
	{
		dup2(cmd->fdo, STDOUT_FILENO);
		close(cmd->fdo);
	}
	if (sts == 127)
		sts = ft_route_fork(g, cmd);
	exit(sts);
}
