/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:34:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/07 18:42:10 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quotinfo	quotinfo_init(void)
{
	t_quotinfo	i;

	i.list1 = NULL;
	i.i = 0;
	i.len = 0;
	i.cmdinfo = NULL;
	i.new_cmd = NULL;
	return (i);
}

t_list	*sepa_cmd(char *cmd, t_list *env_list, t_ms *ms)
{
	t_quotinfo	quotinfo;
	t_list		*ret;

	quotinfo = quotinfo_init();
	ret = NULL;
	while (cmd && cmd[quotinfo.i] && cmd[quotinfo.i] == ' ')
		++quotinfo.i;
	while (cmd[quotinfo.i])
	{
		if (cmd[quotinfo.i] != '\''
			&& cmd[quotinfo.i] != '"' && cmd[quotinfo.i] != ' ')
		{
			ret = part_nq(cmd, env_list, ms, &quotinfo);
			if (ret != NULL)
				return (ret);
		}
		if (cmd[quotinfo.i] == '\'')
		{
			quotinfo.i++;
			ret = part_sq(cmd, &quotinfo);
			if (ret != NULL)
				return (ret);
		}
		if (cmd[quotinfo.i] == '"')
		{
			quotinfo.i++;
			ret = part_dq(cmd, env_list, ms, &quotinfo);
			if (ret != NULL)
				return (ret);
		}
		++quotinfo.i;
	}
	return (quotinfo.list1);
}

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
	cmds = malloc(sizeof(char *) * (len + 1));
	while (list_after_parsing && i < len)
	{
		cmds[i] = list_after_parsing->content;
		list_after_parsing = list_after_parsing -> next;
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}
