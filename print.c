/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:28:23 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/10 18:29:01 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_list *cmd_list)
{
	while (cmd_list)
	{
		current_cmd = *(t_cmd *)cmd_list->content;
		while (current_cmd.cmd[i])
		{
			printf("cmd[%d] = %s\n", i, current_cmd.cmd[i]);
			i++;
		}
		i = 0;
		cmd_list = cmd_list->next;
	}
}
