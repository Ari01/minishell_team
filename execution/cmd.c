/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:27:35 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/07 16:36:13 by dchheang         ###   ########.fr       */
/*   Updated: 2021/09/17 17:27:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_builtin(t_ms *ms, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		ret = ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "cd")) 
		ret = ft_cd(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "pwd")) 
		ret = ft_pwd();
	else if (!ft_strcmp(cmd->cmd[0], "exit")) 
		ret = ft_exit(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "env")) 
		ret = ft_env(ms->env_list, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		ret = ft_export(cmd, ms->env_list); // 头部=1 next 2 next 3
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		ret = ft_unset(cmd, &ms->env_list); // 删除=1 头部变成2
	return (ret);
}

int		run_cmd(t_ms *ms, t_cmd *cmd)
{
	int	ret;

	if (is_builtin(cmd->cmd[0]))
		ret = run_builtin(ms, cmd);
	else
		ret = run_exec(ms, cmd);
	return (ret);
}
