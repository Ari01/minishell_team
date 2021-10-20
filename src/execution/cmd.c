/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:27:35 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/20 06:33:20 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_fork_builtin(t_ms *ms, t_cmd *cmd)
{
	int	pid;
	int	signal;

	signal = 0;
	pid = fork();
	if (!pid)
	{
		if (!ft_strcmp(cmd->cmd[0], "echo"))
			signal = ft_echo(cmd);
		else if (!ft_strcmp(cmd->cmd[0], "pwd"))
			signal = ft_pwd();
		else if (!ft_strcmp(cmd->cmd[0], "env"))
			signal = ft_env(ms->env_list, cmd);
		exit_child(ms, signal);
	}
	else
	{
		waitpid(pid, &signal, 0);
		signal = WEXITSTATUS(signal);
	}
	return (signal);
}

int	run_builtin(t_ms *ms, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		ret = ft_cd(cmd, ms->env_list);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		ret = ft_exit(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		ret = ft_export(cmd, ms->env_list);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		ret = ft_unset(cmd, &ms->env_list);
	return (ret);
}

int	run_cmd(t_ms *ms, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (cmd && cmd->cmd[0])
		cmd->cmd[0] = ft_strlowcase(cmd->cmd[0]);
	if (is_builtin(cmd->cmd[0]))
	{
		if (!ft_strcmp(cmd->cmd[0], "cd")
			|| !ft_strcmp(cmd->cmd[0], "exit")
			|| !ft_strcmp(cmd->cmd[0], "export")
			|| !ft_strcmp(cmd->cmd[0], "unset"))
			ret = run_builtin(ms, cmd);
		else
			ret = run_fork_builtin(ms, cmd);
	}
	else
		ret = run_exec(ms, cmd);
	return (ret);
}
