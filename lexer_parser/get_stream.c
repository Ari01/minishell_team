/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:17:10 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/29 18:11:05 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	update_io(t_list *ite, t_cmd *current_cmd, t_cmd new_cmd)
{
	t_cmd	*next_cmd;

	next_cmd = (t_cmd *)ite->next->content;
	if (current_cmd->flag == SLR || current_cmd->flag == DLR)
	{
		free(new_cmd.in_file);
		new_cmd.in_file = ft_strdup(next_cmd->cmd[0]);
		new_cmd.in_flag = current_cmd->flag;
	}
	else
	{
		free(new_cmd.out_file);
		new_cmd.out_file = ft_strdup(next_cmd->cmd[0]);
		new_cmd.out_flag = current_cmd->flag;
	}
	remove_elem_from_array(next_cmd->cmd);
	return (new_cmd);
}

t_cmd	*save_redir(t_cmd *current_cmd, t_cmd new_cmd)
{
	current_cmd->in_flag = new_cmd.in_flag;
	current_cmd->out_flag = new_cmd.out_flag;
	if (new_cmd.in_file)
		current_cmd->in_file = ft_strdup(new_cmd.in_file);
	if (new_cmd.out_file)
		current_cmd->out_file = ft_strdup(new_cmd.out_file);
	return (current_cmd);
}

t_cmd	get_redir(t_list **cmd_list, t_list **ite, t_cmd *current_cmd, t_cmd new_cmd)
{
	t_cmd	*next_cmd;

	if (!current_cmd->cmd[0])
	{
		new_cmd = update_io(*ite, current_cmd, new_cmd);
		*ite = remove_current_ite(cmd_list, *ite);
	}
	else
	{
		next_cmd = current_cmd;
		while (*ite && is_redir(next_cmd->flag))
		{
			next_cmd = (t_cmd *)(*ite)->content;
			new_cmd = update_io(*ite, next_cmd, new_cmd);
			if (!next_cmd->cmd[0])
				*ite = remove_current_ite(cmd_list, *ite);
			else
				*ite = (*ite)->next;
			next_cmd = (t_cmd *)(*ite)->content;
			if (next_cmd->cmd[0])
			{
				current_cmd->cmd = array_join(current_cmd->cmd, next_cmd->cmd);
				reset_array(next_cmd->cmd);	
			}
		}
		current_cmd = save_redir(current_cmd, new_cmd);
		current_cmd->flag = next_cmd->flag;
		new_cmd = new_io_cmd();
	}
	return (new_cmd);
}

t_list	*get_stream(t_list *cmd_list)
{
	t_list	*ite;
	t_cmd	*current_cmd;
	t_cmd	new_cmd;

	ite = cmd_list;
	new_cmd = new_io_cmd();
	while (ite)
	{
		current_cmd = (t_cmd *)ite->content;
		if (is_redir(current_cmd->flag))
			new_cmd = get_redir(&cmd_list, &ite, current_cmd, new_cmd);
		else if (!current_cmd->cmd[0])
			ite = remove_current_ite(&cmd_list, ite);
		else
		{
			current_cmd = save_redir(current_cmd, new_cmd);
			ite = ite->next;
		}
	}
	return (cmd_list);
}
