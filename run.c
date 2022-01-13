/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:18:42 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/13 18:18:54 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_builtin(t_state *g, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args, cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (printf("%s\n", ft_getcwd()) == -1);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (chdir(cmd->args[1]) == -1);
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(cmd->args, cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "export") && !cmd->args[1])
		return (ft_env(cmd->args, cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "export") && cmd->args[1])
		return (ft_export(g, cmd->args, cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(g, cmd->args, cmd->envp));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(g, cmd->args, cmd->envp));
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
	int		sts;

	if (cmd->fdi != -1)
		stdi = ft_dupi(cmd);
	if (cmd->fdo != -1)
		stdo = ft_dupo(cmd);
	cmd->envp = ft_envtostr(g->envlst);
	sts = ft_builtin(g, cmd);
	pid = fork();
	if (!pid && sts == 127)
		exit(ft_exec(g, cmd));
	if (!pid && sts != 127)
		exit(sts);
	if (cmd->fdi != -1)
		dup2(stdi, STDIN_FILENO);
	if (cmd->fdo != -1)
		dup2(stdo, STDOUT_FILENO);
	return (pid);
}
