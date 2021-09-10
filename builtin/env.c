/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:09:30 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/10 17:55:51 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_cmd *cmd)
{
    char * p;         

    if (!cmd || cmd->cmd[0] == NULL || cmd->cmd[1] != NULL)
        return (ERROR);
    p = getenv("PATH");
    ft_putstr_fd("PATH=", STDOUT_FILENO);
    ft_putstr_fd(p, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
    return (SUCCESS);         
}