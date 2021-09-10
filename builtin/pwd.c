/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:59:25 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/10 13:31:59 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  ft_pwd(t_cmd *cmd)
{
    char *path;
    
    if (cmd && cmd->cmd[1] != NULL)
        printf("pwd: too many arguments\n");
    else
    {
        path = getcwd(NULL, 0);
        printf("%s\n", path);
        free(path);
    }
}