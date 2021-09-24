/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:31:37 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/24 19:28:55 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_redir(int flag)
{
	return (flag == SLR || flag == DLR || flag == SRR || flag == DRR);
}

t_cmd	*get_redir(t_cmd *cmd, char **cmd_array, int flag)
{
	if (flag == SLR || flag == DLR)
	{
		cmd->in_file = ft_strdup(cmd_array[0]);
		cmd->in_flag = flag;
	}
	else
	{
		cmd->out_file = ft_strdup(cmd_array[0]);
		cmd->out_flag = flag;
	}
	remove_elem_from_array(cmd_array);
	return (cmd);
}

void	get_stream(t_list *cmd_list)
{
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;
	t_list	*ite;
	char	**join;

	ite = cmd_list;
	while (ite)
	{
		current_cmd = (t_cmd *)ite->content;
		if (is_redir(current_cmd->flag))
		{
			next_cmd = (t_cmd *)ite->next->content;
			if (!current_cmd->cmd[0])
			{
				next_cmd = get_redir(next_cmd, next_cmd->cmd, current_cmd->flag);
				ite = ite->next;
			}
			else
			{
				while (ite && is_redir(current_cmd->flag))
				{
					current_cmd = get_redir(current_cmd, next_cmd->cmd, current_cmd->flag);
					join = array_join(current_cmd->cmd, next_cmd->cmd);
					free_array(current_cmd->cmd);
					current_cmd->cmd = join;
					current_cmd->flag = next_cmd->flag;
					remove_from_list(&cmd_list, ite->next);
					ite = ite->next;
					if (ite)
						next_cmd = (t_cmd *)ite->content;
				}
			}
		}
		else
			ite = ite->next;
	}
}

/*
void	get_stream(t_list *cmd_list)
{
	t_list	*ite;
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;
	t_cmd	*tmp_cmd;

	ite = cmd_list;
	while (ite)
	{
		current_cmd = (t_cmd *)ite->content;
		if (is_redir(current_cmd->flag))
		{
			if (!current_cmd->cmd[0])
			{
				remove_from_list(&cmd_list, ite);
				ite = cmd_list;
			}
			next_cmd = (t_cmd *)ite->next->content;
			tmp_cmd = get_redir(next_cmd->cmd, current_cmd->flag);
			if (!next_cmd->cmd)
				remove_from_list(&cmd_list, ite->next);
		}
		else
		{
			current_cmd = copy_redir(current_cmd, new_cmd);
			
		}
	}
}*/
