/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:34:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/05 17:11:51 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check dollar function
// - if true -> return true else false
// static void _cmdinfo_(t_cmdinfo **cmdinfo, char *cmd, int i, int len)
// {
        
//             *cmdinfo = creat_cmdinfo();
//             (*cmdinfo)->cmd = ft_substr(cmd, i, len);
// }

t_list *sepa_cmd(char *cmd, t_list *env_list, t_ms *ms) //返回一个cmd链表的节点
{
    t_list *list1 = NULL;  // 一个链表的一个节点
    int i = 0;
    int len = 0;
    t_cmdinfo *cmdinfo; //一个节点里面的数据
    char *new_cmd = NULL;

    while (cmd && cmd[i] && cmd[i] == ' ')
        ++i;
    while (cmd[i])
    {
        if (cmd[i] != '\'' && cmd[i] != '"' && cmd[i] != ' ')
        {
            len = 0;
            while (cmd[i + len] && cmd[i + len] != '\'' &&  cmd[i + len] != '"' && cmd[i + len] != ' ')
                ++len;   //i不变
            //_cmdinfo_(&cmdinfo, cmd, i, len);
            cmdinfo = creat_cmdinfo();
            cmdinfo->cmd = ft_substr(cmd, i, len);  //取得一小节字符 没有符号
            if (check_dollar(cmdinfo->cmd))
            {
                new_cmd = hanlding_dollar(cmdinfo->cmd, env_list, ms);
                cmdinfo->cmd  = new_cmd;
            }
            i = i + len;
            if (cmd[i] == ' ' || cmd[i] == '\0')
                cmdinfo->status = NO_TOUCH;
            else
                cmdinfo->status = TO_MERGE;
            ft_lstadd_back(&list1, ft_lstnew((void*)cmdinfo));
            if(cmd[i] == '\0')
                return (list1);
        }
        if (cmd[i] == '\'')
        {
            i++;
            if (cmd[i] == '\'')   //如果下位还是单引号
            {
                cmdinfo = creat_cmdinfo();
                cmdinfo->cmd = ft_strdup("");  //malloc一个空字符
                if(cmd[i + 1] == ' ' || cmd[i + 1] == '\0')
                    cmdinfo->status = NO_TOUCH;
                else
                    cmdinfo->status = TO_MERGE;
                ft_lstadd_back(&list1, ft_lstnew((void*)cmdinfo));
                if(cmd[i] == '\0')
                    return (list1);
            }
            else
            {
                len = 0;
                while (cmd[i + len] && cmd[i + len] != '\'')
                    ++len;
                cmdinfo = creat_cmdinfo();
                cmdinfo->cmd = ft_substr(cmd, i, len);
                i = i + len;
                if(cmd[i + 1] == ' ' || cmd[i + 1] == '\0')
                    cmdinfo->status = NO_TOUCH;
                else
                    cmdinfo->status = TO_MERGE;
                ft_lstadd_back(&list1, ft_lstnew((void*)cmdinfo));
                if(cmd[i] == '\0')
                    return (list1);
            }
        }
        if (cmd[i] == '"')
        {
            i++;
            if (cmd[i] == '"')   //如果下位还是单引号
            {
                cmdinfo = creat_cmdinfo();
                cmdinfo->cmd = ft_strdup("");  //malloc一个空字符
                if(cmd[i + 1] == ' ' || cmd[i + 1] == '\0')
                    cmdinfo->status = NO_TOUCH;
                else
                    cmdinfo->status = TO_MERGE;
                ft_lstadd_back(&list1, ft_lstnew((void*)cmdinfo));
                if(cmd[i] == '\0')
                    return (list1);
            }
            else
            {                
                len = 0;
                while (cmd[i + len] && cmd[i + len] != '"')
                    ++len;
                cmdinfo = creat_cmdinfo();
                cmdinfo->cmd = ft_substr(cmd, i, len);
                if (check_dollar(cmdinfo->cmd))
                {
                    new_cmd = hanlding_dollar(cmdinfo->cmd, env_list, ms);
                    cmdinfo->cmd  = new_cmd;
                }
                i = i + len;
                if(cmd[i + 1] == ' ' || cmd[i + 1] == '\0')
                    cmdinfo->status = NO_TOUCH;
                else
                    cmdinfo->status = TO_MERGE;
                ft_lstadd_back(&list1, ft_lstnew((void*)cmdinfo));
                if(cmd[i] == '\0')
                    return (list1);
            }
        }
        ++i;    
    }
    return (list1);
}

char *cmd_merge(t_list *list1)  //所有cmd的链表 里面有cmd->cmd ->status   //创建新地址保存字符串
{
    char *merge_cmd = NULL;
    while(list1)     
    {
        if (((t_cmdinfo *)list1->content)->status == TO_MERGE)
            merge_cmd = ft_join(merge_cmd, ((t_cmdinfo *)list1->content)->cmd);  //NULL + 当前的cmd
        else
            break;
        list1 = list1->next;
    }
    merge_cmd = ft_join(merge_cmd, ((t_cmdinfo *)list1->content)->cmd);
    return (merge_cmd);   //返回新的字符串
}

t_list *new_list(t_list *cmd)
{
    t_list *new_list = NULL;
    char *new_cmd = NULL;

    while (cmd)
    {
        if (((t_cmdinfo *)cmd->content)->status == TO_MERGE)
        {
            new_cmd = cmd_merge(cmd);
            while (((t_cmdinfo *)cmd->content)->status == TO_MERGE)
                cmd = cmd->next;
            cmd = cmd->next;
            ft_lstadd_back(&new_list, ft_lstnew((void *)new_cmd));
        }
        else
        {
            new_cmd = ((t_cmdinfo *)cmd->content)->cmd;
            ft_lstadd_back(&new_list, ft_lstnew((void *)new_cmd));
            cmd = cmd->next;
        }
    }
    return (new_list);
}
char **lst_to_tab(char *cmd, t_list *env_list, t_ms *ms)  //one cmd 
{
    char **cmds = NULL;
    int len = 0;
    int i = 0;
    t_list *tmp = NULL;
    t_list *list_after_parsing = NULL; 
		
    tmp = sepa_cmd(cmd, env_list, ms); 
    list_after_parsing = new_list(tmp);
    
    len = ft_lstsize(list_after_parsing);
    cmds = malloc(sizeof(char *) * (len + 1));
    while (list_after_parsing && i < len)
    {
        cmds[i] = list_after_parsing->content;
        list_after_parsing = list_after_parsing -> next;
        i++;
    }
    cmds[i] = NULL;
    return cmds;  //获得一个c**cmd的数据
}


