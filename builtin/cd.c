/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:15 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/04 17:03:59 by xuwang           ###   ########.fr       */
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
        return (ERROR);
    else if (cmd && cmd->cmd[1] != NULL && !(check_file(cmd)))
    {   
        print_msg("prompt: cd: ", cmd->cmd[1], ": No such file or directory\n", STDERR_FILENO);
        return (ERROR);
    }
    else if (cmd && cmd->cmd[1] && check_file(cmd))
    {
        if (!chdir(cmd->cmd[1]))
            return (ERROR);
    }
    return (SUCCESS);
}