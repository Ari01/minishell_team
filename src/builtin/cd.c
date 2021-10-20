/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:15 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/20 06:05:44 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_home(void)
{
	if (chdir(getenv("HOME")) == -1)
	{
		print_msg("minishell: cd: HOME not set\n", NULL, NULL, STDOUT_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int	ft_cd(t_cmd *cmd)
{
	if (!cmd)
		return (ERROR);
	if (cmd && ! cmd->cmd[1])
	{
		if (check_home() == ERROR)
			return (ERROR);
	}
	else if (cmd && cmd->cmd[1] != NULL)
	{
		if (chdir(cmd->cmd[1]) != -1)
			return (SUCCESS);
		else
		{
			printf("bash: cd: %s: :%s\n", cmd->cmd[1], strerror(errno));
			return (ERROR);
		}
	}
	return (SUCCESS);
}
