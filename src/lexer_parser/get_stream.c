/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:17:10 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/23 12:08:42 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	update_io(t_list *ite, t_cmd *current_cmd, t_cmd new_cmd)
{
	t_cmd	*next_cmd;
	t_io	*io;

	next_cmd = (t_cmd *)ite->next->content;
	io = malloc(sizeof(*io));
	io->flag = current_cmd->flag;
	io->file = ft_strdup(next_cmd->cmd[0]);
	if (current_cmd->flag == SLR || current_cmd->flag == DLR)
		ft_lstadd_back(&new_cmd.in_streams, ft_lstnew(io));
	else
		ft_lstadd_back(&new_cmd.out_streams, ft_lstnew(io));
	remove_elem_from_array(next_cmd->cmd);
	return (new_cmd);
}

t_cmd	*save_redir(t_cmd *current_cmd, t_cmd new_cmd)
{
	current_cmd->in_streams = new_cmd.in_streams;
	current_cmd->in_stream_head = current_cmd->in_streams;
	current_cmd->out_streams = new_cmd.out_streams;
	current_cmd->out_streams_head = current_cmd->out_streams;
	return (current_cmd);
}

t_cmd	*get_next_redir(t_list **cmd_list,
	t_list **ite,
	t_cmd *current_cmd,
	t_cmd *new_cmd)
{
	t_cmd	*next_cmd;
	char	**tmp;

	next_cmd = current_cmd;
	while (*ite && is_redir(next_cmd->flag))
	{
		*new_cmd = update_io(*ite, next_cmd, *new_cmd);
		if (!next_cmd->cmd[0])
			*ite = remove_current_ite(cmd_list, *ite);
		else
			*ite = (*ite)->next;
		next_cmd = (t_cmd *)(*ite)->content;
		if (next_cmd->cmd[0])
		{
			tmp = array_join(current_cmd->cmd, next_cmd->cmd);
			free_array(current_cmd->cmd);
			current_cmd->cmd = tmp;
			reset_array(next_cmd->cmd);
		}
	}
	return (next_cmd);
}

void	get_redir(t_list **cmd_list, t_list **ite, t_cmd *current_cmd)
{
	t_cmd	*next_cmd;
	t_cmd	new_cmd;

	new_cmd = new_io_cmd();
	while (is_redir(current_cmd->flag) && !current_cmd->cmd[0])
	{
		new_cmd = update_io(*ite, current_cmd, new_cmd);
		*ite = remove_current_ite(cmd_list, *ite);
		current_cmd = (t_cmd *)(*ite)->content;
	}
	next_cmd = get_next_redir(cmd_list, ite, current_cmd, &new_cmd);
	current_cmd = save_redir(current_cmd, new_cmd);
	current_cmd->flag = next_cmd->flag;
}

t_list	*get_stream(t_list *cmd_list)
{
	t_list	*ite;
	t_cmd	*current_cmd;

	ite = cmd_list;
	while (ite)
	{
		current_cmd = (t_cmd *)ite->content;
		if (is_redir(current_cmd->flag))
		{
			get_redir(&cmd_list, &ite, current_cmd);
			ite = ite->next;
		}
		else if (!current_cmd->cmd[0] && current_cmd->flag)
			ite = remove_current_ite(&cmd_list, ite);
		else
			ite = ite->next;
	}
	return (cmd_list);
}
