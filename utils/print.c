/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:28:23 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/22 16:40:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_list *cmd_list)
{
	t_cmd	current_cmd;
	int		i;

	while (cmd_list)
	{
		current_cmd = *(t_cmd *)cmd_list->content;
		i = 0;
		while (current_cmd.cmd[i])
		{
			printf("cmd[%d] = %s\n", i, current_cmd.cmd[i]);
			printf("flag = %d, outstream = %s, intstream = %s\n", current_cmd.flag, current_cmd.out_stream, current_cmd.in_stream);
			i++;
		}
		cmd_list = cmd_list->next;
	}
}
