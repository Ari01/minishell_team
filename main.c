/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:41 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/09 17:08:02 by dchheang         ###   ########.fr       */
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
		while (cmd_list)
		{
			current_cmd = *(t_cmd *)cmd_list->content;
			while (current_cmd.cmd[i])
			{
				printf("cmd[%d] = %s\n", i, current_cmd.cmd[i]);
				i++;
			}
			printf("flag = %d\n", current_cmd.flag);
			cmd_list = cmd_list->next;
			i = 0;
		}
    }
    return 0;
}
