/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:18:42 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/17 18:36:39 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_cd(char **args)
{
	if (!ft_strlen(args[1]))
	{
		ft_putstr(1, "Invalid path\n");
		return (1);
	}
	if (chdir(args[1]) == -1)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	return (0);
}

int	ft_builtin(t_state *g, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd->args));
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(g, cmd->args, cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(g, cmd->args));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(g, cmd->args));
	return (127);
}

int	ft_dupi(t_cmd *cmd)
{
	int	stdi;

	stdi = dup(STDIN_FILENO);
	dup2(cmd->fdi, STDIN_FILENO);
	close(cmd->fdi);
	return (stdi);
}

int	ft_dupo(t_cmd *cmd)
{
	int	stdo;

	stdo = dup(STDOUT_FILENO);
	dup2(cmd->fdo, STDOUT_FILENO);
	close(cmd->fdo);
	return (stdo);
}

pid_t	ft_run(t_state *g, t_cmd *cmd)
{
	int		pid;
	int		stdi;
	int		stdo;

	if (cmd->fdi != -1)
		stdi = ft_dupi(cmd);
	if (cmd->fdo != -1)
		stdo = ft_dupo(cmd);
	cmd->envp = ft_envtostr(g->envlst);
	if (!cmd->envp)
		return (0);
	cmd->sts = ft_builtin(g, cmd);
	pid = fork();
	if (!pid && cmd->sts == 127)
		exit(ft_exec(g, cmd));
	if (!pid && cmd->sts != 127)
		exit(cmd->sts);
	if (cmd->fdi != -1)
		dup2(stdi, STDIN_FILENO);
	if (cmd->fdo != -1)
		dup2(stdo, STDOUT_FILENO);
	return (pid);
}
