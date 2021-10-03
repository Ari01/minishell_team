/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:11:12 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/03 15:04:28 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strisdigit(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}

int ft_exit(t_cmd *cmd)
{
    if(!cmd)
        return (ERROR);
    else if (cmd && cmd->cmd[1] && cmd->cmd[2] && ft_strisdigit(cmd->cmd[1]))   //第一位都是数字。第二位存在不退出
    {
        ft_putstr_fd("exit\n", STDIN_FILENO);
        printerror("prompt: exit: too many arguments", NULL, NULL);
        return (ERROR);
    }
    else if (cmd && cmd->cmd[1] && !(ft_strisdigit(cmd->cmd[1])))  //第一位有不是数字的 退出
    {
        ft_putstr_fd("exit\n", STDIN_FILENO);
        printerror("prompt: exit: ", cmd->cmd[1], ": numeric argument required");
        exit(0);
    }
    else
    {
        ft_putstr_fd("exit\n", STDIN_FILENO);
        exit(0);
    }
    return (SUCCESS);
}