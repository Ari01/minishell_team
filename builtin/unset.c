/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:53:21 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/04 16:56:04 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*unset no option */
static int check_is_cmd(char *s)   //name must a-z, A-Z, _
{
    int i;
    
    i = 0;
    while(s[i])
    {
        if (!(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z') && s[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

 static t_list *check_name_exist(char *cmd, t_list *env_list) 
{
    int len;

    len = 0;
    if (check_is_cmd(cmd)) //len of env name 
    {
        len = ft_strlen(cmd);
        // printf("cmd: [%s] len: [%d]\n",cmd,  len);
    }
    while (env_list)   //check one env in env_list
    {
        if (ft_strncmp(cmd, (char *)env_list->content, len) == 0 && 
            (((char *)env_list->content)[len] == '\0' || ((char *)env_list->content)[len] == '='))
        {
            return (env_list);
        }
        env_list = env_list->next;
    }
    return (NULL);
}

static t_list *del_env(char *cmd, t_list *env_list)  //delete env
{
    t_list *to_del;
    t_list *tmp = NULL;
    t_list *prev = NULL;
    
    tmp = env_list;  //tmp是头地址
    to_del = check_name_exist(cmd, env_list);
    
    if (!to_del)
        return env_list;
    /*del env*/
    while (tmp && tmp != to_del)   //前一个tmp的地址给prev 直到找到to del
    {
        prev = tmp;
        tmp = tmp->next;
    }
    
    if (tmp == to_del)  //找到
    {
        if (prev == NULL)  //如果是头地址
        {
            // printf("head [%p] - next [%p]\n", env_list, tmp->next);
            env_list = tmp->next;   //头地址变成要删除的节点的下一个地址，头节点删除
        }
        else
        {
            prev->next = tmp->next; //tmp的前地址prev的下一个节点 变成要删的下一个地址 ，头节点删除
        }
        if (tmp) {
            // printf("to free: [%s]\n", (char *)tmp->content);
            free(tmp->content);
            tmp->content = NULL;
            free(tmp);
            tmp = NULL;
        }
    }
    return env_list;
}


int  ft_unset(t_cmd *cmd, t_list **env_list)
{
    int i;
    
    i = 1;
    if (!cmd || !cmd->cmd[1])
        return (ERROR);
    while (cmd && cmd->cmd[i]) 
    {
        if (!(check_is_cmd(cmd->cmd[i])))
            print_msg("minishell: unset: `", cmd->cmd[i],  "\': not a valid identifier\n", STDERR_FILENO);
        else
            *env_list = del_env(cmd->cmd[i], *env_list);
        i++;
    }
    return (SUCCESS);
}
