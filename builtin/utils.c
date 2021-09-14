/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:47:49 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/14 16:11:08 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *get_env(char **env, t_list *env_list)
{
    int i;

    i = 0;
    while (env[i])
    {
        ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(env[i])));
        i++;
    }
    return (env_list);
}

void ft_list_sort(t_list **begin_list, int (*ft_strcmp)()) // Ver.1 : change content.
{
    t_list *list;
    void *data;

    list = *begin_list;
    while (list && list->next)
    {
        if (ft_strcmp(list->content, list->next->content) > 0)
        {
            data = list->content;
            list->content = list->next->content;
            list->next->content = data;
            list = *begin_list;
        }
        else
            list = list->next;
    }
}


void printerror(char *msg1, char *msg2, char *msg3) 
{
    ft_putstr_fd(msg1, STDERR_FILENO);
    ft_putstr_fd(msg2, STDERR_FILENO);
    ft_putstr_fd(msg3, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}
