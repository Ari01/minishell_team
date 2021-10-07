/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:27:35 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/07 18:42:26 by dchheang         ###   ########.fr       */
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

/*
static int check1(char *cmd)
{
	int i = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\'' || cmd[i] == '"')
		{
			i++;
			if (cmd[i] == ' ')
				return (1);
		}
	}
	return (0);
}

static char *new_str(char *cmd1)
{
	char *str = NULL;
	int i = 0;
	int len = ft_strlen(cmd1);
	while (cmd1[i] && (cmd[i] == '\'' || cmd[i] == '"' || cmd[i] == ' ' )
		i++;
	str = ft_substr(cmd1, i, len-i);
	while (cmd1[i] && (cmd[i] != '\'' && cmd[i] != '"' && cmd[i] != ' ' )
		i++;
	str = ft_substr(str, 0, len-i);
	return (str);
}*/

int		run_cmd(t_ms *ms, t_cmd *cmd)
{
	int	ret;

/*	 if (cmd && check1(cmd->cmd[0]))
	 	print_msg("prompt:", new_str );*/
	if (cmd && cmd->cmd[0])
		cmd->cmd[0] = ft_strlowcase(cmd->cmd[0]);
	if (is_builtin(cmd->cmd[0]))
		ret = run_builtin(ms, cmd);
	else
		ret = run_exec(ms, cmd);
	return (ret);
}
