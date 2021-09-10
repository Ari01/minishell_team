/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:15 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/10 18:16:18 by xuwang           ###   ########.fr       */
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

void printerror(char *msg1, char *msg2) {
    ft_putstr_fd(msg1, STDERR_FILENO);
    ft_putstr_fd(msg2, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}

int ft_cd(t_cmd *cmd)
{
    if (cmd && cmd->cmd[1] == NULL)
        return 0;
    else if (cmd && cmd->cmd[2] != NULL)
        printerror("cd: string not in pwd: ", cmd->cmd[1]);
    else if (cmd && cmd->cmd[1] != NULL && !(check_file(cmd)))
        printerror("cd: no such file or directory: ", cmd->cmd[1]);
    else if (cmd && cmd->cmd[1] && check_file(cmd))
    {
        if (!chdir(cmd->cmd[1]))
            return (ERROR);
    }
    return (SUCCESS);
}