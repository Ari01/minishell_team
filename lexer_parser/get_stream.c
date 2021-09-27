/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:31:37 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/27 15:22:27 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_redir(int flag)
{
	return (flag == SLR || flag == DLR || flag == SRR || flag == DRR);
}

t_list	*get_redir(t_list *cmd_list, t_list *ite, char **infile, char **outfile)
{
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;
	t_list	*tmp;

	current_cmd = (t_cmd *)ite->content;
	next_cmd = (t_cmd *)ite->next->content;
	if (current_cmd->flag == SLR || current->cmd->flag == DLR)
		*infile = ft_strdup(next_cmd->cmd[0]);
	else
		*outfile = ft_strdup(next_cmd->cmd[0]);
	remove_elem_from_array(next_cmd->cmd);
	if (!current_cmd->cmd[0])
	{
		tmp = ite;
		ite = ite->next;
		remove_from_list(&cmd_list, tmp);
	}
	return (ite);
}

void	get_stream(t_list *cmd_list)
{
	t_cmd	*current_cmd;
	t_list	*ite;
	char	*infile;
	char	*outfile;

	infile = NULL;
	outfile = NULL;
	ite = cmd_list;
	while (ite)
	{
		current_cmd = (t_cmd *)ite->content;
		if (is_redir(current_cmd->flag))
			get_redir(ite, current_cmd, &infile, &outfile);
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
