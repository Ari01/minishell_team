/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stream_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:55:05 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/13 10:49:08 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(int flag)
{
	return (flag == SLR || flag == DLR || flag == SRR || flag == DRR);
}

t_list	*remove_current_ite(t_list **cmd_list, t_list *ite)
{
	t_list	*itmp;

	(void)cmd_list;
	itmp = ite;
	ite = ite->next;
	remove_from_list(cmd_list, itmp);
	return (ite);
}

void	reset_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = 0;
		i++;
	}
}

t_cmd	new_io_cmd(void)
{
	t_cmd	cmd;

	cmd.in_streams = NULL;
	cmd.out_streams = NULL;
	return (cmd);
}
