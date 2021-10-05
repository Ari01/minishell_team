/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:28:23 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/04 19:09:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_list *cmd_list)
{
	t_cmd	current_cmd;
	t_io	io;
	int		i;

	while (cmd_list)
	{
		current_cmd = *(t_cmd *)cmd_list->content;
		i = 0;
		while (current_cmd.cmd[i])
		{
			printf("cmd[%d] = %s\n", i, current_cmd.cmd[i]);
			i++;
		}
		printf("infile = %s\n", current_cmd.in_stream.file);
		while (current_cmd.out_streams)
		{
			io = *(t_io *)current_cmd.out_streams->content;
			printf("outfile = %s\n", io.file);
			current_cmd.out_streams = current_cmd.out_streams->next;
		}
		cmd_list = cmd_list->next;
	}
}
