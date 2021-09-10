/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:09:30 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/10 17:28:40 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_cmd *cmd)
{
    char * p;         

    if (!cmd || cmd->cmd[0] == NULL || cmd->cmd[1] != NULL)
        return (ERROR);
    p = getenv("PATH")
    printf("PATH =%s\n",p);
    return (SUCCESS);         
}