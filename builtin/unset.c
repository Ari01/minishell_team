/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:53:21 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/12 19:21:06 by xuwang           ###   ########.fr       */
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
        if (!(s[0] >= 'A' && s[0] <= 'Z') && !(s[0] >= 'a' && s[0] <= 'z') && s[0] != '_' )
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
        len = ft_strlen(cmd);
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

static void del_env(char *cmd, t_list *env_list)  //delete env
{
    t_list *to_del;
    
    to_del = check_name_exist(cmd, env_list);
    /*del env*/
    while (env_list)
    {
        if ((env_list->next = to_del) && to_del->next)
        {
            env_list->next = to_del->next;
            free(to_del);
        }
        env_list = env_list->next;
    }
}


void  ft_unset(t_cmd *cmd, t_list *env_list)
{
    int i;
    int j;
    
    i = 1;
    while (cmd && cmd->cmd[i]) 
    {
        if (!(check_is_cmd(cmd->cmd[i])))
            printerror("minishell: unset: `", cmd->cmd[i],  "\': not a valid identifier");
        i++;
    }
    j = 0;
    while (cmd && cmd->cmd[j]) 
    {
        del_env(cmd->cmd[i], env_list);
        i++;
    }
}
