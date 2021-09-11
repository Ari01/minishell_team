/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:47:49 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/11 15:23:36 by xuwang           ###   ########.fr       */
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