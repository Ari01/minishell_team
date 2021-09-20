/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:34:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/21 00:48:30 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define STATUS_OPEN 1
#define STATUS_CLOSE 0
#define IS_SQ 1
#define IS_DQ 2
#define NO_Q 0

    

t_quot quote_init(void) {
    t_quot quote_info;
    
    quote_info.quot = NO_Q;
    quote_info.quot_status = STATUS_CLOSE;

    return quote_info;
}



/**
 * 命令: echo                    "'" "'""test hello" "test2" " " ok
 * 
 * 1) 根据cmd的空格计算cmd的length, 方便分开他们比如:
 * // 需要malloc
 * echo "hello" " " "test"
 * ---->>>>
 * cmds[0]: echo
 * cmds[1]: "'" 
 * cmds[2]: "'""test hello"
 * cmds[3]: "test2"
 * cmds[4]: " "
 * cmds[5]: ok
 * cmds[6]: NULL
 * 
 * 2) 然后每个cmds[x]个个处理, 比如:
 * cmds[2]: "'""test hello" ---> test hello
*/

int cmds_len(char *cmd) {
    int i = 0;
    int len = 1;
    t_quot quote_info = quote_init();

    while (cmd && cmd[i]) {
        if (cmd[i] == '\'') {
            if (quote_info.quot == IS_DQ) {
                ++i;
                continue;
            }
            quote_info.quot = IS_SQ;
            if (quote_info.quot_status == STATUS_CLOSE)
                quote_info.quot_status = STATUS_OPEN;
            else {
                quote_info.quot_status = STATUS_CLOSE;
                quote_info.quot = NO_Q;
            }
        }
        else if (cmd[i] == '\"') {
            if (quote_info.quot == IS_SQ) {
                ++i;
                continue;
            }
            quote_info.quot = IS_DQ;
            if (quote_info.quot_status == STATUS_CLOSE)
                quote_info.quot_status = STATUS_OPEN;
            else {
                quote_info.quot_status = STATUS_CLOSE;
                quote_info.quot = NO_Q;
            }
        }
        if (cmd[i] == ' ' && quote_info.quot_status == STATUS_CLOSE)
        {
            ++len;
            while (cmd[i + 1] == ' ')
                ++i;
        }
        ++i;
    }
    return len;
}

// void    parse_cmd_quote(char *cmd) {
//     int i = 0;

//     while (cmd && cmd[i]) {
        
            
//     }
// }

int main() {
    int i = cmds_len("echo      \'\"\'        \"\'\" \"\'\"\"test hello\" \"test2\" \" \" ok");
    printf("len : [%d]\n", i);
    return 0;
}


char  *hanling_quot(t_ms *ms, t_quot quot)
{
       
        
        
       
}



