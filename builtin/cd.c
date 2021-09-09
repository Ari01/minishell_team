/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:15 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/09 20:54:14 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(t_cmd *cmd)
{
    if (cmd && cmd->cmd[2] != 0)
        printf("cd: string not in pwd: %s", cmd->cmd[1]);
    else if (cmd && cmd->cmd[1])
    {
        if (!chdir(cmd->cmd[1]))
            return (ERROR);
    }
    return (SUCCESS);
}

int main(void) 
{
    t_cmd *echo_cmd;

    echo_cmd = malloc(sizeof(t_cmd));
    char *cmd[4];

    cmd[0] = "cd";
    cmd[1] = "1";
    cmd[2] = "2";
   // cmd[3] = NULL;

    echo_cmd->cmd = cmd;
    // ft_echo(echo_cmd);
    free(echo_cmd);
    return 0;
}
