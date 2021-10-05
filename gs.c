/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:31:37 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/27 19:35:53 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_redir(int flag)
{
	return (flag == SLR || flag == DLR || flag == SRR || flag == DRR);
}

t_cmd	get_io_files(t_cmd cmd, int flag, char *file_name)
{
	cmd.io_flag = flag;
	if (flag == SLR || flag == DLR)
	{
		free(cmd.in_file);
		cmd.in_file = ft_strdup(file_name);
	}
	else
	{
		free(cmd.out_file);
		cmd.out_file = ft_strdup(file_name);
	}
	return (cmd);
}

t_list	*get_redir(t_list *cmd_list, t_list *ite, t_cmd *ctmp)
{
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;
	t_list	*ltmp;

	if (!ite)
		return (ite);
	current_cmd = (t_cmd *)ite->content;
	while (ite && is_redir(current_cmd->flag))
	{
		current_cmd = (t_cmd *)ite->content;
		next_cmd = (t_cmd *)ite->next->content;
		*ctmp = get_io_files(*ctmp, current_cmd->flag, next_cmd->cmd[0]);
		remove_elem_from_array(next_cmd->cmd);
		if (!current_cmd->cmd[0])
		{
			ltmp = ite;
			ite = ite->next;
			remove_from_list(&cmd_list, ltmp);
		}
		else
			break;
	}
	return (ite);
}

t_list	*get_stream(t_list *cmd_list)
{
	t_cmd	*new_cmd;
	t_cmd	ctmp;
	t_list	*ite;

	ctmp.in_file = NULL;
	ctmp.out_file = NULL;
	ctmp.io_flag = 0;
	ite = cmd_list;
	while (ite)
	{
		ite = get_redir(cmd_list, ite, &ctmp);
		if (ite)
		{
			new_cmd = (t_cmd *)ite->content;
			ite = ite->next;
			ite = get_redir(cmd_list, ite, &ctmp);
			new_cmd->io_flag = ctmp.io_flag;
			if (ctmp.in_file)
				new_cmd->in_file = ft_strdup(ctmp.in_file);
			if (ctmp.out_file)
				new_cmd->out_file = ft_strdup(ctmp.out_file);
			free(ctmp.in_file);
			free(ctmp.out_file);
			ctmp.in_file = NULL;
			ctmp.out_file = NULL;
			if (ite)
				ite = ite->next;
		}
	}
	return (cmd_list);
}
