/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:11:12 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/19 15:27:33 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_cmd *cmd)
{
    if (cmd && cmd->cmd[1] != NULL)
         printerror("exit: too many arguments", NULL, NULL);
    else
        exit(0);
}