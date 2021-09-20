/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:34:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/20 18:27:16 by xuwang           ###   ########.fr       */
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

int check_quot_exit(char *s)
{
    int i = 0;
     
    while (s[i])
    {
        if (s[i + 1] == '"' || s[i] == '\'')
            return (1);        
    }
    return (0);
}
// int check_first_quot(char *str)
// {
//     int i = 0;
//     int len = 0;

//     while (str[i])
//     {
//         if (str[i] == '"')
//             len++;
//         else 
//             break;
//         i++;
//     }
//     return (len);
// }



// char *del_quot(char *str)
// {


//     char *s = NULL;
//    int i = 0;

//    while (str[i] && is_quot(str[i]) == 0) 
//         i++;
//     printf("%d\n", i);
//     s = malloc(sizeof(char) * i + 1);
//     if (!s)
    
//         return (NULL);

//     int len = 0;
//     int j = 0;
//     while (str[len + i] && is_quot(str[len + i]) == 0)
//     {
//         s[j] = str[len + i];
//         j++;
//         len++;
//     }
//     s[j] = '\0';
//     return (s);
// }


// void hanling_quot(t_ms *ms, t_quot quot)
// {
    // int i = 0;
    // int len = 0;
   
    // while (cmd->cmd[i])
    // {
    //     quot =init_quot(quot); 
    //  
    //     quot = get_quot(cmd->cmd[i], quot); // get if have sing quot or doubl quot;
    //     len = check_first_quot(cmd->cmd[i]); //get number of len de first quot;
    //     if(len % 2 == 0)
    //         quot.paire = 1;
    //     else
    //         quot.impaire = 1;
    //     if ((quot.doub_quot == 1 && quot.sing_quot != 1)   //just only one type de quot;
    //         || (quot.doub_quot != 1 && quot.sing_quot == 1))
    //         del_quot(cmd->cmd[i++]);                      // del quot;
    //     else if (quot.doub_quot == 1 && quot.sing_quot == 1 && quot.impaire == 1) //if first quot is impaire
    //     {
            
    //     }
    //     else if 
    // }
    
    
    char  *hanling_quot(t_ms *ms, t_quot quot)
    {
        char *tmp = ms->rdl;  
        int i = 0;
        int j = 0;
            
        while(ms->rdl[i] && (ms->rdl[i] != '"' && ms->rdl[i] != '\'')) //first place of quot
            i++;
        while(ms->rdl[i] && (ms->rdl[i + 1] != '"' && ms->rdl[i] != '\''))  // i is close quot
            tmp[j++] = ms->rdl[i++]; 
           // arg =ft_split(ms->rdl, ' ');  //sepa str par espase like : e"ch"o "a bc" 'ws w''|' "123" | echo "2ee" 
        
        
       return (tmp);
    }
    

