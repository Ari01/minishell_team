/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:01 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/29 17:31:07 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_cmd *cmd)
{
    int i;
    int n;

    n = 0;
    i = 1;
	// j'ai modifie : s'il n'y a pas d'argument, echo imprime \n
	if (!cmd->cmd[1])
		ft_putendl_fd("", STDOUT_FILENO);
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
}
