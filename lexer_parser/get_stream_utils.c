/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stream_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:55:05 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/28 19:02:11 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_redir(int flag)
{
	return (flag == SLR || flag == DLR || flag == SRR || flag == DRR);
}

t_list	*remove_current_ite(t_list **cmd_list, t_list *ite)
{
	t_list	*itmp;

	itmp = ite;
	ite = ite->next;
	remove_from_list(cmd_list, itmp);
	return (ite);
}

void	reset_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = 0;
		i++;
	}
}

t_cmd	new_io_cmd()
{
	t_cmd	cmd;

	cmd.in_flag = 0;
	cmd.out_flag = 0;
	cmd.in_file = NULL;
	cmd.out_file = NULL;
	return (cmd);
}
