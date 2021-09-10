/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:01 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/10 16:54:10 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_cmd *cmd)
{
    int i;
    int n;

    n = 0;
    i = 1;
    while (cmd && cmd->cmd[i] && (ft_strcmp(cmd->cmd[i], "-n") == 0))
    {
        i++;
        n = 1;
    }
    while (cmd && cmd->cmd[i])
    {
        printf("%s", cmd->cmd[i]);
        if (cmd->cmd[i + 1])
            printf(" ");
        else if(!cmd->cmd[i + 1] && n == 0)
            printf("\n");
        i++;
    }
}
