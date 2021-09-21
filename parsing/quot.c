/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:34:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/21 19:09:38 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * 命令: echo                    "'" "'""test hello" "test2" " " ok
 * 
 * 1) 根据cmd的空格计算cmd的length, 方便分开他们比如:
 * // 需要malloc
 * echo      \'\"\'        \"\'\" \"\'\"\"test hello\" \"test2\" \" \" ok
 * ---->>>>
 * cmds[0]: echo
 * cmds[1]: '"' 
 * cmds[2]: "'"
 * cmds[3]: "'"
 * cmds[4]: "test hello"
 * cmds[5]: "test2"
 * cmds[6]: " "
 * cmds[7]: ok
 * cmds[8]: NULL
 * 
 * 2) 然后每个cmds[x]个个处理, 比如:
 * cmds[2]: "'""test hello" ---> 'test hello
*/
t_quot quote_init(void) {
    t_quot quote_info;
    
    quote_info.quot = NO_Q;
    quote_info.quot_status = STATUS_CLOSE;
    return quote_info;
}

t_list *sepa_cmd(char *cmd) {
    int i = 0;
    int len = 0;
    
    int start = -1;
    int end = -1;
    t_list *cmd_lst = NULL;

    t_quot quote_info = quote_init();
    while (cmd && cmd[i]) 
    {
        if (cmd[i] == '\'') 
        {
            if (quote_info.quot == IS_DQ)
            {
                ++i;
                continue;
            }
            quote_info.quot = IS_SQ;
            if (quote_info.quot_status == STATUS_CLOSE) {
                quote_info.quot_status = STATUS_OPEN;
                start = i + 1;
            }
            else {
                quote_info.quot_status = STATUS_CLOSE;
                quote_info.quot = NO_Q;
                end = i;
            }
        }
        else if (cmd[i] == '"') 
        {
            if (quote_info.quot == IS_SQ) {
                ++i;
                continue;
            }
            quote_info.quot = IS_DQ;
            if (quote_info.quot_status == STATUS_CLOSE) {
                quote_info.quot_status = STATUS_OPEN;
                start = i + 1;
            }
            else {
                quote_info.quot_status = STATUS_CLOSE;
                quote_info.quot = NO_Q;
                end = i;
            }
        }
        else if (quote_info.quot == NO_Q)
        {
            if (quote_info.quot_status == STATUS_CLOSE) {
                quote_info.quot_status = STATUS_OPEN;
                start = i;
            }
            if (cmd[i] == ' ' || cmd[i + 1] == '\0') {
                if (quote_info.quot_status == STATUS_OPEN) {
                    quote_info.quot_status = STATUS_CLOSE;
                    if (cmd[i + 1] == '\0')
                        end = i + 1;
                    else
                        end = i;
                }
            }
        }
        if ((cmd[i] == ' ' || cmd[i + 1] == '\0') && quote_info.quot_status == STATUS_CLOSE)
        {
            ++len;
            while (cmd[i + 1] == ' ')
                ++i;
        }
        if (start != -1 && end != -1)
        {
            if (end - start > 0) {
                ft_lstadd_back(&cmd_lst, ft_lstnew(ft_substr(cmd, start, (end - start))));
            }
            start = -1;
            end = -1;
        }
        ++i;
    }
    return cmd_lst;
}


char **lst_to_tab(char *cmd)  //one cmd 
{
    char **cmds = NULL;
    int len;
    int i = 0;
    t_list *tmp = NULL;
		
    tmp = sepa_cmd(cmd); //一个flag的cmd的链表
    len = ft_lstsize(tmp);
    cmds = malloc(sizeof(char *) * len + 1);
    while (tmp && i < len)
    {
        cmds[i] = tmp->content;
        tmp = tmp -> next;
        i++;
    }
    cmds[i] = NULL;
    return cmds;  //获得一个c**cmd的数据
}

// int main() {
//    //t_list *cmd = sepa_cmd("echo \'\"\'        \"\'\" \"\'\"\"test hello\" \"test2\" \" \" ok");
//     t_list *cmd = sepa_cmd("echo \"   |\" \'\'\"test hello\"");
//     while (cmd != NULL) {
//         printf("cmd : [%s]\n", cmd->content);
//         cmd = cmd->next;
//     }
//     return 0;
// }




