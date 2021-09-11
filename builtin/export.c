/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:28:22 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/11 20:10:29 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
ordre A-Z , -, -- 
add declare -x 
value after '=' add ""
*/
static void ft_list_sort(t_list **begin_list, int (*ft_strcmp)()) // Ver.1 : change content.
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

static int check_name(char *s)
{
    if ((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z') || s[0] == '_' )
        return (1);
    return (0);
}

static int check_name_exist(char *cmd, t_list *env_list)
{
    int len;
    int i;

    i = 0;
    len = 0;
    while (cmd && cmd[i] != '=')
    {
        len++;
        i++;
    }
    if (ft_strncmp(cmd, (char *)env_list->content, len) == 0)
        return (1);
    return (0);
    
}

/*
export a A BC 1 -->yes  bash: export: `1': not a valid identifier
export "ab e"  -->no  bash: export: `ab e': not a valid identifier
export "ab=e" -->yes
export 1 2 -->no
            bash: export: `1': not a valid identifier
            bash: export: `2': not a valid identifier
export A=1 1 A -->yes bash: export: `1': not a valid identifier (A=1) 
$ export A=1  A=3 -->yes change A=3
*/
static t_list *add_chang_export(t_cmd *cmd, t_list *env_list)
{
    /* add element */
    if (check_name(cmd->cmd[1]) && !(check_name_exist((cmd->cmd[1]), env_list)))
        ft_lstadd_back(&env_list, ft_lstnew((void *)cmd->cmd[1]));
    /* change element */
    else if (check_name(cmd->cmd[1]) && check_name_exist((cmd->cmd[1]), env_list)) //chang.
        env_list->content = cmd->cmd[1];
    return (env_list);
}

static char *print_export(char *str)
{
    int i;

    i = 0;
    
    ft_putstr_fd("declare -x ", STDOUT_FILENO);
    while (str && str[i])
    {
        if (str[i] == '=')
        {
            ft_putchar_fd('=', STDOUT_FILENO);
            ft_putchar_fd('\"', STDOUT_FILENO);
        }
        else
            ft_putchar_fd(str[i], STDOUT_FILENO);
            
        i++;
    }
    if (ft_strchr(str, '='))
        ft_putchar_fd('\"', STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
    
    return (str);
}

void ft_export(t_cmd *cmd, t_list *env_list)
{
    int i;
    int j;

    j = 1;
    i = 1;
    while (cmd && cmd->cmd[j] != NULL) //return ERROR
    {
        if (!(check_name(cmd->cmd[j])))
        {
            printerror("minishell: export: `", cmd->cmd[j],  "\': not a valid identifier");
        }
        j++;
    }
    while (cmd && cmd->cmd[i] && check_name(cmd->cmd[i]) ) 
    {
        add_chang_export(cmd, env_list);
        i++;
    }
    ft_list_sort(&env_list, &ft_strcmp);
    while (cmd->cmd[1] == NULL && env_list && env_list->content)
    {
        print_export((char *)env_list->content);
        env_list = env_list->next;
    }
}
