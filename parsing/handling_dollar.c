/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:54:05 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/27 20:54:49 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int check_dollar(char *cmd)
// {
//     int i = 0;
//     while (cmd[i])
//     {
//         if (cmd[i] == '$')
//             return (1); 
//     }
//     return (0);
// }

//改变一个引号内的$就行
int check_name(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' ))
}
static t_list  *get_dollar_name(char *cmd)   //get $PATH   
{
    int i = 0;
    int len = 0;
    int start = 0;
    char *env = NULL;
    t_list *dollor_list = NULL;
    while (cmd[i])
    {
        if (cmd[i] == '$')
        {
            start = i;
            while (cmd[i + len] && cmd[i + len] != '"' && cmd[i + len] != '\0' && cmd[i + len] != ' ')
            {
                if (!check_name(cmd[i + len]))
                    break;
                else
                {
                    len++;
                    env = ft_substr(*cmd, start, len);
                    ft_lstadd_back(&dollor_list, ft_lstnew());
                    
                }
                i++;
            }
        }
        i++;
    }
    return (dollor_list);
}

// int main()
// {
//     char *s = "1derty $test 123";
//     char *env = get_dollar_name(s);
//     printf("%s", env);
// }

char  *change_dollar(char **cmd, t_ms ms)
{
    char *env = get_dollar_name(&cmd);  //env = &PATH
    char *value = NULL;
    int i = 0;
   
    
        if (check_name_exist(env++, ms.env_list) != NULL) //env的下一位开始在list找
        {
            value = ft_strdup((char *)ms.env_list->content); //把找到的list放在value地址
            while (value[i] && value[i] != '=')
            i++;
        i += 1;  //走到 = 下一位
        value = ft_substr((char *)ms.env_list->content, i, (ft_strlen(value) - i));
        return (value);
    }     
    else
        printerror("\n", NULL, NULL);
}

