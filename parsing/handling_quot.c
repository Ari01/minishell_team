/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:34:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/07 18:42:10 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_quotinfo
{
    int i;
    int len;
    char *new_cmd;
    t_list *list1;
    t_cmdinfo *cmdinfo; //一个节点里面的数据
} t_quotinfo;

t_quotinfo quotinfo_init()
{
    t_quotinfo i;

    i.list1 = NULL;  // 一个链表的一个节点
    i.i = 0;
    i.len = 0;
    i.cmdinfo = NULL; //一个节点里面的数据
    i.new_cmd = NULL;
    return i;
}
void check_status(char c, t_quotinfo *quotinfo)
{
    if (c == ' ' || c == '\0')
        quotinfo->cmdinfo->status = NO_TOUCH;
    else
        quotinfo->cmdinfo->status = TO_MERGE;
}

void parser_dollar(t_quotinfo *quotinfo, t_list *env_list, t_ms *ms)
{
    if (check_dollar(quotinfo->cmdinfo->cmd))
    {
        quotinfo->new_cmd = hanlding_dollar(quotinfo->cmdinfo->cmd, env_list, ms);
        quotinfo->cmdinfo->cmd  = quotinfo->new_cmd;
    }
}

t_list    *part_nq(char *cmd, t_list *env_list, t_ms *ms, t_quotinfo *quotinfo) 
{
    quotinfo->len = 0;
    while (cmd[quotinfo->i + quotinfo->len] && cmd[quotinfo->i + quotinfo->len] != '\'' 
        &&  cmd[quotinfo->i + quotinfo->len] != '"' && cmd[quotinfo->i + quotinfo->len] != ' ')
        ++quotinfo->len;   //i不变
    quotinfo->cmdinfo = creat_cmdinfo();
    quotinfo->cmdinfo->cmd = ft_substr(cmd, quotinfo->i, quotinfo->len);  //取得一小节字符 没有符号
    parser_dollar(quotinfo, env_list, ms);
    quotinfo->i = quotinfo->i + quotinfo->len;
    check_status(cmd[quotinfo->i], quotinfo);
    ft_lstadd_back(&quotinfo->list1, ft_lstnew((void*)quotinfo->cmdinfo));
    if(cmd[quotinfo->i] == '\0')
        return (quotinfo->list1);
    return NULL;
}

t_list    *part_sq(char *cmd, t_quotinfo *quotinfo)
{
    if (cmd[quotinfo->i] == '\'')   //如果下位还是单引号
    {
        quotinfo->cmdinfo = creat_cmdinfo();
        quotinfo->cmdinfo->cmd = ft_strdup("");  //malloc一个空字符
        check_status(cmd[quotinfo->i + 1], quotinfo);
        ft_lstadd_back(&quotinfo->list1, ft_lstnew((void*)quotinfo->cmdinfo));
        if(cmd[quotinfo->i] == '\0')
            return (quotinfo->list1);
    }
    else
    {
        quotinfo->len = 0;
        while (cmd[quotinfo->i + quotinfo->len] && cmd[quotinfo->i + quotinfo->len] != '\'')
            ++quotinfo->len;
        quotinfo->cmdinfo = creat_cmdinfo();
        quotinfo->cmdinfo->cmd = ft_substr(cmd, quotinfo->i, quotinfo->len);
        quotinfo->i = quotinfo->i + quotinfo->len;
        check_status(cmd[quotinfo->i + 1], quotinfo);
        ft_lstadd_back(&quotinfo->list1, ft_lstnew((void*)quotinfo->cmdinfo));
        if(cmd[quotinfo->i] == '\0')
            return (quotinfo->list1);
    }
    return NULL;
}
t_list    *part_dq(char *cmd, t_list *env_list, t_ms *ms, t_quotinfo *quotinfo)
{
    if (cmd[quotinfo->i] == '"')   //如果下位还是单引号
    {
        quotinfo->cmdinfo = creat_cmdinfo();
        quotinfo->cmdinfo->cmd = ft_strdup("");  //malloc一个空字符
        check_status(cmd[quotinfo->i + 1], quotinfo);
        ft_lstadd_back(&quotinfo->list1, ft_lstnew((void*)quotinfo->cmdinfo));
        if(cmd[quotinfo->i] == '\0')
            return (quotinfo->list1);
    }
    else
    {                
        quotinfo->len = 0;
        while (cmd[quotinfo->i + quotinfo->len] && cmd[quotinfo->i + quotinfo->len] != '"')
            ++quotinfo->len;
        quotinfo->cmdinfo = creat_cmdinfo();
        quotinfo->cmdinfo->cmd = ft_substr(cmd, quotinfo->i, quotinfo->len);
        parser_dollar(quotinfo, env_list, ms);
        quotinfo->i = quotinfo->i + quotinfo->len;
        check_status(cmd[quotinfo->i + 1], quotinfo);
        ft_lstadd_back(&quotinfo->list1, ft_lstnew((void*)quotinfo->cmdinfo));
        if(cmd[quotinfo->i] == '\0')
            return (quotinfo->list1);
    }
    return NULL;
}


t_list *sepa_cmd(char *cmd, t_list *env_list, t_ms *ms) //返回一个cmd链表的节点
{
    t_quotinfo quotinfo = quotinfo_init();
    t_list *ret = NULL;

    while (cmd && cmd[quotinfo.i] && cmd[quotinfo.i] == ' ')
        ++quotinfo.i;
    while (cmd[quotinfo.i])
    {
        if (cmd[quotinfo.i] != '\'' && cmd[quotinfo.i] != '"' && cmd[quotinfo.i] != ' ')
        {
            ret = part_nq(cmd, env_list, ms, &quotinfo);
            if (ret != NULL)
                return ret;
        }
        if (cmd[quotinfo.i] == '\'')
        {
            quotinfo.i++;
            ret = part_sq(cmd, &quotinfo);
            if (ret != NULL)
                return ret;
        }
        if (cmd[quotinfo.i] == '"')
        {
            quotinfo.i++;
            ret = part_dq(cmd, env_list, ms, &quotinfo);
            if (ret != NULL)
                return ret;
        }
        ++quotinfo.i;    
    }
    return (quotinfo.list1);
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


