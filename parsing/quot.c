/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:34:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/19 20:35:48 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quot init_quot(t_quot quot)
{
    ft_bzero(&quot, sizeof(t_quot));
    return (quot);
}
t_quot get_quot(char *str, t_quot quot)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '"')
            quot.doub_quot = 1;
        if (str[i] == '\'')
            quot.sing_quot = 1;
        i++;
    }
    return (quot);
}
int check_first_quot(char *str)
{
    int i = 0;
    int len = 0;

    while (str[i])
    {
        if (str[i] == '"')
        {   
            len++;
            i++;
        }
        else 
            break;
    }
    return (len);
}

char *del_quot(char *str)
{
   char *s;
   int i = 0;
   int j = 0;
   int len =0;
   
   while (str[i] && str[i] != '"' && str[i] != '\'')
   {
        len++;
        i++;
   }
   s = malloc(sizeof(char) *len + 1);
   if (!s)
        return (NULL);
    i = 0;
    while (str[i] && j < len && str[i] != '"' && str[i] != '\'' )
    {
        s[j] = str[i];
        i++;
        j++;
    }
    s[j] = '\0';
    return (s);
    printf("%s", s);
}

void hanling_quot(t_cmd *cmd, t_quot quot)
{
    int i = 0;
    int len = 0;
   
   
    while (cmd->cmd[i])
    {
        quot =init_quot(quot); 
        quot = get_quot(cmd->cmd[i], quot); // get if have sing quot or doubl quot;
        len = check_first_quot(cmd->cmd[i]); //get number of len de first quot;
        if(len % 2 == 0)
            quot.paire = 1;
        else
            quot.impaire = 1;
        if ((quot.doub_quot == 1 && quot.sing_quot != 1)   //just only one type de quot;
            || (quot.doub_quot != 1 && quot.sing_quot == 1))
            del_quot(cmd->cmd[i++]);                      // del quot;
        else if (quot.doub_quot == 1 && quot.sing_quot == 1 && quot.impaire == 1) //if first quot is impaire
        {
            
        }
        else if 
        i++;
    }
    
    
        
}

