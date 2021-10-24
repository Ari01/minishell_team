/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:28:23 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/23 12:01:14 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_array(t_cmd current_cmd)
{
	int	i;

	i = 0;
	while (current_cmd.cmd[i])
	{
		printf("cmd[%d] = %s\n", i, current_cmd.cmd[i]);
		i++;
	}
}

void	print_streams(t_list *stream, char *name)
{
	t_io	io;

	while (stream)
	{
		io = *(t_io *)stream->content;
		printf("%s = %s\n", name, io.file);
		stream = stream->next;
	}
}

void	print_cmds(t_list *cmd_list)
{
	t_cmd	*current_cmd;

	while (cmd_list)
	{
		current_cmd = (t_cmd *)cmd_list->content;
		printf("flag = %d\n", current_cmd->flag);
		print_cmd_array(*current_cmd);
		print_streams(current_cmd->in_streams, "infile");
		print_streams(current_cmd->out_streams, "outfile");
		cmd_list = cmd_list->next;
	}
}
