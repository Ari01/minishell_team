/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:47:49 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/11 20:07:38 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *get_env(char **env, t_list *env_list)
{
    int i;

    i = 1;
    while (env[i])
    {
        ft_lstadd_back(&env_list, ft_lstnew((void *)env[i]));
        i++;
    }
    return (env_list);
}

void printerror(char *msg1, char *msg2, char *msg3) {
    ft_putstr_fd(msg1, STDERR_FILENO);
    ft_putstr_fd(msg2, STDERR_FILENO);
    ft_putstr_fd(msg3, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}