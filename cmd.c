/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:27:35 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/19 19:17:21 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_builtin(t_ms *ms, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "cd")) 
		ft_cd(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "pwd")) 
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "exit")) 
		ft_exit(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "env")) 
		ft_env(ms->env_list);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		ft_export(cmd, ms->env_list); // 头部=1 next 2 next 3
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		ft_unset(cmd, &ms->env_list); // 删除=1 头部变成2
}

void	run_cmd(t_ms *ms, t_cmd *cmd)
{
	if (is_builtin(cmd->cmd[0]))
		run_builtin(ms, cmd);
	else
		run_exec(ms, cmd);
}
