/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:27:35 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/13 17:24:14 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd(t_cmd *cmd)
{
	char	*s;
	char	buff[BUFFER_SIZE];
	int		nbytes;
	t_list	*env_list;

	env_list = NULL;
	env_list = get_env(env, env_list);
	s = ft_strdup("");
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "cd")) 
		ft_cd(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "pwd")) 
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "exit")) 
		ft_exit();
	else if (!ft_strcmp(cmd->cmd[0], "env")) 
		ft_env(env_list);
	else if (!ft_strcmp(cmd->cmd[0], "export")) 
		ft_export(cmd, env_list);
	else if (!ft_strcmp(cmd->cmd[0], "lc"))
	{
		while (1)
		{
			if ((nbytes = read(STDIN_FILENO, buff, BUFFER_SIZE - 1)) > 0)
			{
				printf("after read\n");
				buff[nbytes] = 0;
				printf("buff = %s\n", buff);
				printf("%zu\n", ft_strlen(buff));
				break;
			}
			printf("sleeping...\n");
			sleep(1);
		}
	}
}
