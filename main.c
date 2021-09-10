/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:41 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/10 14:52:48 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printcmd(t_cmd *cmd) {
    int i =0;
    
    if (cmd) {
        printf("-- -- --\n");
        while (cmd->cmd && cmd->cmd[i]) {
            printf("cmd: [%s]\n", cmd->cmd[i++]);
        }
        printf("-- -- --\n");
    }
}

int main(void) {
    char    *rdl;
	t_cmd	current_cmd;
    t_list  *cmd_list;
	int		i;

	i = 0;
    while (1)
    {
        rdl = readline("prompt> ");
		cmd_list = get_cmds(rdl);
        current_cmd = *(t_cmd *)cmd_list->content;
        // printcmd(&*(t_cmd *)cmd_list->content);
        if (!ft_strcmp(current_cmd.cmd[0], "echo"))
            ft_echo(&current_cmd);
        else if (!ft_strcmp(current_cmd.cmd[0], "cd")) 
            ft_cd(&current_cmd);
        else if (!ft_strcmp(current_cmd.cmd[0], "pwd")) 
            ft_pwd(&current_cmd);
        else if (!ft_strcmp(current_cmd.cmd[0], "exit")) 
            ft_exit();
        
    }
    return 0;
}
