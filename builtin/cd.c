/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:15 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/10 14:10:03 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_file(t_cmd *cmd)
{
    int fd;
    const char *path;

    path = cmd->cmd[1];
    if ((fd = open(path, O_RDONLY)) == -1)
        return (0);
    return (1);
}

int ft_cd(t_cmd *cmd)
{
    if (cmd && cmd->cmd[1] == NULL)
        return 0;
    else if (cmd && cmd->cmd[2] != NULL)
        printf("cd: string not in pwd: %s\n", cmd->cmd[1]);
    else if (cmd && cmd->cmd[1] != NULL && !(check_file(cmd)))
         printf("cd: no such file or directory: %s\n", cmd->cmd[1]);
    else if (cmd && cmd->cmd[1] && check_file(cmd))
    {
        if (!chdir(cmd->cmd[1]))
            return (ERROR);
    }
    return (SUCCESS);
}