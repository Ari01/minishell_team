/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:09:30 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/11 16:42:53 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* check if a env variable have "=" (value) */

void ft_env(t_list *env_list)
{
    while (env_list)
    {
        if (ft_strchr((char *)env_list->content, '='))
        {
            ft_putstr_fd((char *)env_list->content, STDOUT_FILENO);
            ft_putstr_fd("\n", STDOUT_FILENO);
        }
        env_list = env_list->next;
    }
}