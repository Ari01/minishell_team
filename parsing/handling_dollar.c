/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:54:05 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/30 15:17:41 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// //echo "1223 $PATH 2w21$ $USER" | echo $PATH
// // static int check_name(char *s)   //name must a-z, A-Z, _
// // {
// //     int i;
    
// //     i = 0;
// //     while(s[i])
// //     {
// //         if (!(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z') && s[i] != '_')
// //             return (0);
// //         i++;
// //     }
// //     return (1);
// // }

// static void  check_exit_add(t_list *_change_, char *dollar, t_list *env_list)   //确认一个list_dollar的值存在与否然后加进去
// {
//     int len = ft_strlen(dollar);
//     char *str = NULL;
//     char *env = NULL;
//     int i = 0;
   
     
//     while (env_list)
//     {
//         if (ft_strncmp(dollar, (char *)env_list->content, len) == 0 &&
//         (((char *)env_list->content)[len] == '\0' || ((char *)env_list->content)[len] == '='))
//         {
//               str = ft_strdup((char *)env_list->content);
//               len = ft_strlen(str);
//               while (str[i] && str[i] != '=')
//                     i++;
//               env = ft_strdup(ft_substr(env_list->content, i, (len-i)));
//               ft_lstadd_back(&_change_, ft_lstnew((void *)env));
//         }
//         else
//         {
//             ft_lstadd_back(&_change_, ft_lstnew((void *)""));
//         }
//         env_list = env_list->next;
//     }
// }


// static t_list *change_list(t_list *_change_, t_list *dollar_list, t_list *env_list)  //确认所有的list_dollar的值存在与否然后加进去 返回一个需要改变的值
// {
    
//     while (dollar_list)
//     {
//         check_exit_add(_change_, (char *)dollar_list->content, env_list);
//         dollar_list = dollar_list->next;
//     }
//     return (_change_);
// }

// t_list  *get_dollar_env(char *rdl, t_list *dollar_list) //保存$后面的list_dollar  exmple: PATH USER 1 abc 
// {
//     char *env = NULL;
//     int start = 0;
//     int i = 0;
//     int len = 0;
//     while (rdl[i])
//     {
//         if (rdl[i] == '$' && rdl[i + 1] != ' ' && rdl[i + 1] != '\0' && rdl[i + 1] != '"'  && rdl[i + i] != '\'' && rdl[i + i] != '$')
//         {
//             start = i + 1;
//             while(rdl[i + len] && rdl[i + len] != ' ' && rdl[i + len] != '\0' && rdl[i + len] != '"'  && rdl[i + len] != '\'' && rdl[i + len] != '$')
//                 len++;
//             env = ft_strdup(ft_substr(rdl, start, (len-1)));
//             ft_lstadd_back(&dollar_list, ft_lstnew((void*)env));
//         }
//         start = 0;
//         len = 0;
//         i++;       
//     }
//     return (dollar_list);
// }


// char  *hanlding_dollar(char *rdl, t_list *env_list)  //创建新的rdl
// {
//     int i = 0;
//     t_list *dollar_list = NULL;
//     dollar_list = get_dollar_env(rdl, dollar_list);
//     t_list *_change_ = NULL;
//     _change_ =  change_list(_change_, dollar_list, env_list);
//     char *new_rdl = ft_strdup("");
//   while (rdl[i])
//   {
//       if(rdl[i] == '$' && rdl[i + 1] != ' ' && rdl[i + i] != '\0' && rdl[i + i] != '"'  && rdl[i + i] != '\'' && rdl[i + i] != '$')
//       {
//           while (_change_)
//           {
//               new_rdl = ft_join(new_rdl, (char *)_change_->content);
//               //_change_ = _change_->next;
//           }
//           while (rdl[i] != ' ' || rdl[i] != '\0' || rdl[i] != '"' || rdl[i] != '\'' || rdl[i] != '$')
//                 i++;
//       }
//     //   else 
//     //   {
//     //       new_rdl = ft_join(new_rdl, &rdl[i]);
//     //   }
//       i++;
//   }
//     return (new_rdl);    
// }
// int main()
// {
//     t_list *new;
//     char *rdl = " echo \"1223 $PATH $1 $ $USER\" | echo $PATH ";
//      new =  get_dollar_env(rdl);
//      while(new)
//      {
//          printf("%s\n", (char *)new->content);
//          new = new->next;
//      }     
//     return (0);
// }

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
       // printf("dollar : %s\n", dollar);
        if (ft_strncmp(dollar, (char *)env_list->content, len) == 0 &&
        (((char *)env_list->content)[len] == '\0' || ((char *)env_list->content)[len] == '='))
        {
             printf("here : env_name : %s\n", (char *)env_list->content);
            return (env_list);
        }
        env_list = env_list->next;
        
    }
    return(NULL);
}

static int check_env_start(char *env)
{
    printf("env_name : %s\n", env);
    int i = 0;
    while (env[i] && env[i] != '=')
        i++;
    //printf("here1:%d\n", i);
    return (i + 1);
   
}

static int check_env_len(char *env)
{
    int start = check_env_start(env);
    int len = ft_strlen(env);
    int i = len - start;
    // printf("here1:%d\n", i);
    return (i);
}

char  *hanlding_dollar(char *cmd, t_list *env_list)  //创建新的rdl
{
    
    int i = 0;
    int start = 0;
    int len = 0;
    char *dollar = NULL;
    char *new_cmd = NULL;
    // char *c = NULL;
    while (cmd[i])
    {
        if(cmd[i] == '$' && cmd[i + 1] != ' ' && cmd[i + 1] != '\0')
        { 
            i++;
            if (cmd[i] >= '0' && cmd[i] <= '9')
            {
                new_cmd = ft_join(new_cmd, "");
                //printf("new_cmd: %s\n", new_cmd);
            }
            else 
            {
                start = i;
                while (cmd[i + len] && cmd[i + len] != ' ' && cmd[i + len] != '\0')
                {
                    len++;
                }
                dollar = ft_substr(cmd, start, len);
                if ((env_list = check_env_exit(dollar, env_list))!= NULL)
                {
                    new_cmd = ft_join(new_cmd, ft_substr((char *)env_list->content, check_env_start((char *)env_list->content), check_env_len((char *)env_list->content)));
                }
                else
                {
                    //printf("new_cmd2: %s\n", new_cmd);
                     new_cmd = ft_join(new_cmd, "");
                }
            }
        }

        else
        {
            // //printf("cmd[i]: %c\n", cmd[i]);
            // printf("cmd : [%s]\n", cmd);
            // c = ft_substr(cmd, i, 1);
            // printf("? : [%s]\n", c);
            // new_cmd = ft_join(new_cmd, c);
            // free(c);
            // c = NULL;
            //printf("new_cmd3: %s\n", new_cmd);
        }
        start = 0;
        len = 0;
        i++;
    }
    return (new_cmd);    
}