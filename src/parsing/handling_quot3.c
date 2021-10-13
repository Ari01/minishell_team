/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quot3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:28:14 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/11 15:28:45 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_merge(t_list *list1)
{
	char	*merge_cmd;

	merge_cmd = NULL;
	while (list1)
	{
		if (((t_cmdinfo *)list1->content)->status == TO_MERGE)
			merge_cmd = ft_join(merge_cmd, ((t_cmdinfo *)list1->content)->cmd);
		else
			break ;
		list1 = list1->next;
	}
	merge_cmd = ft_join(merge_cmd, ((t_cmdinfo *)list1->content)->cmd);
	return (merge_cmd);
}

t_list	*new_list(t_list *cmd)
{
	t_list	*new_list;
	char	*new_cmd;

	new_list = NULL;
	new_cmd = NULL;
	while (cmd)
	{
		if (((t_cmdinfo *)cmd->content)->status == TO_MERGE)
		{
			new_cmd = cmd_merge(cmd);
			while (((t_cmdinfo *)cmd->content)->status == TO_MERGE)
				cmd = cmd->next;
			cmd = cmd->next;
			ft_lstadd_back(&new_list, ft_lstnew((void *)new_cmd));
		}
		else
		{
			new_cmd = ((t_cmdinfo *)cmd->content)->cmd;
			ft_lstadd_back(&new_list, ft_lstnew((void *)new_cmd));
			cmd = cmd->next;
		}
	}
	return (new_list);
}

char	**lst_to_tab(char *cmd, t_list *env_list, t_ms *ms)
{
	char	**cmds;
	int		len;
	int		i;
	t_list	*tmp;
	t_list	*list_after_parsing;

	cmds = NULL;
	len = 0;
	i = 0;
	tmp = NULL;
	list_after_parsing = NULL;
	tmp = sepa_cmd(cmd, env_list, ms);
	list_after_parsing = new_list(tmp);
	len = ft_lstsize(list_after_parsing);
	ft_lstclear(&tmp, free);
	cmds = malloc(sizeof(char *) * (len + 1));
	tmp = list_after_parsing;
	while (tmp && i < len)
	{
		cmds[i] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&list_after_parsing, &free);
	cmds[i] = NULL;
	return (cmds);
}
