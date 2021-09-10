/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:41 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/10 13:19:47 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void) {
    char    *rdl;
	int		i;
	t_cmd	current_cmd;
    t_list  *cmd_list;

	i = 0;
    while (1)
    {
        rdl = readline("prompt> ");
		cmd_list = get_cmds(rdl);
        while (cmd_list)
		{
			current_cmd = *(t_cmd *)cmd_list->content;
			if (current_cmd.flag == '|')
				run_pipe(cmd_list);
		}
    }
    return 0;
}
