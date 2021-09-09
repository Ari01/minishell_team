/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:41 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/09 18:01:00 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        if (!ft_strcmp(current_cmd.cmd[0], "echo"))
            ft_echo(&current_cmd);
    }
    return 0;
}
