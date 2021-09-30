/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:54:05 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/30 15:51:13 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_dollar(char *cmd)
{
    int i= 0;
    while (cmd[i])
    {
        if (cmd[i] == '$')
            return(1);
        i++;
    }
    return (0);
}
static t_list *check_env_exit(char *dollar, t_list *env_list)
{
    int len = ft_strlen(dollar);
    
    while (env_list)
    {
        if (ft_strncmp(dollar, (char *)env_list->content, len) == 0 &&
        (((char *)env_list->content)[len] == '\0' || ((char *)env_list->content)[len] == '='))
        {
            return (env_list);
        }
        env_list = env_list->next;
        
    }
    return(NULL);
}

static int check_env_start(char *env)
{
    int i = 0;
    while (env[i] && env[i] != '=')
        i++;
    return (i + 1);
   
}

static int check_env_len(char *env)
{
    int start = check_env_start(env);
    int len = ft_strlen(env);
    int i = len - start;
    return (i);
}

char  *hanlding_dollar(char *cmd, t_list *env_list)  //创建新的rdl
{
    
    int i = 0;
    int start = 0;
    int len = 0;
    char *dollar = NULL;
    char *new_cmd = NULL;
    char *c = NULL;
    while (cmd[i])
    {
        if(cmd[i] == '$' && cmd[i + 1] != ' ' && cmd[i + 1] != '\0')
        { 
            i++;
            if (cmd[i] >= '0' && cmd[i] <= '9')
            {
                new_cmd = ft_join(new_cmd, "");
                i++;
                if (cmd[i] != '\0' && cmd[i] != ' ')
                {
                    start = i;
                    while (cmd[i] && cmd[i] != '\0' && cmd[i] != ' ')
                        i++;
                    new_cmd = ft_join(new_cmd, ft_substr(cmd, start, i - start));
                }
            }
            else 
            {
                start = i;
                while (cmd[i + len] && cmd[i + len] != ' ' && cmd[i + len] != '\0')
                    len++;
                dollar = ft_substr(cmd, start, len);
                if ((env_list = check_env_exit(dollar, env_list))!= NULL)
                    new_cmd = ft_join(new_cmd, ft_substr((char *)env_list->content, check_env_start((char *)env_list->content), check_env_len((char *)env_list->content)));
                else
                     new_cmd = ft_join(new_cmd, "");
                i = i + len;
            }
        }
        else
        {
            c = ft_substr(cmd, i, 1);
            new_cmd = ft_join(new_cmd, c);
            free(c);
            c = NULL;
        }
        start = 0;
        len = 0;
        i++;
    }
    return (new_cmd);    
}