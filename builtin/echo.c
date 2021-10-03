/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:01 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/03 14:03:22 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(t_cmd *cmd)
{
    int i;
    int n;

    n = 0;
    i = 1;
    if (!cmd || !cmd->cmd[i])
    {
         ft_putstr_fd("\n", STDOUT_FILENO);
         return(ERROR);
    }
    while (cmd && cmd->cmd[i] && (ft_strcmp(cmd->cmd[i], "-n") == 0))
    {
        i++;
        n = 1;
    }
    while (cmd && cmd->cmd[i])
    {
        ft_putstr_fd(cmd->cmd[i], STDOUT_FILENO);
        if (cmd->cmd[i + 1])
            ft_putstr_fd(" ", STDOUT_FILENO);
        else if(!cmd->cmd[i + 1] && n == 0)
            ft_putstr_fd("\n", STDOUT_FILENO);
        i++;
    }
    return (SUCCESS);
}
