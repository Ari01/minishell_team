/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:44:25 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/22 16:39:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int		is_redirection(char c)
{
	return (c == SLR || c == DLR || c == SRR || c == DRR);
}

t_list	*redirect_remove(t_cmd *cmd)
{
	char	*stream;

	if (cmd->flag == SLR || cmd->flag == DLR)
		stream = cmd->in_stream;
	else
		stream = cmd->out_stream;
	next_cmd->stream = ft_strdup(next_cmd->cmd[0]);
	remove_elem_from_array(next_cmd->cmd);
	ite = ite->next;
	return (ite);
}

t_list	*redirect_join_remove()
{
	char	**join;

	cmd->stream = next_cmd->cmd[0];
	if (next_cmd->cmd[1])
	{
		remove_elem_from_array(next_cmd->cmd);
		join = array_join(cmd->cmd, next_cmd->cmd);
		free_array(cmd->cmd);
		cmd->cmd = join;
	}
}

void	get_stream(t_list **cmd_list)
{
	t_cmd	*cmd;
	t_cmd	*next_cmd;
	t_list	*ite;
	t_list	*tmp;

	ite = *cmd_list;
	while (ite)
	{
		cmd = (t_cmd *)ite->content;
		if (is_redirection(cmd->flag))
		{
			next_cmd = (t_cmd *)ite->next->content;
			if (!cmd->cmd[0])
				redirect_remove();
			else
				redirect_join_remove();
			tmp = ite->next;
			ite = ite->next->next;
			remove_from_list(cmd_list, tmp);
		}
		else
			ite = ite->next;
	}
}*/
