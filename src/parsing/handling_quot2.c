/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quot2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:34:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/19 15:54:44 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_status(char c, t_quotinfo *quotinfo)
{
	if (c == ' ' || c == '\0')
		quotinfo->cmdinfo->status = NO_TOUCH;
	else
		quotinfo->cmdinfo->status = TO_MERGE;
}

void	parser_dollar(t_quotinfo *quotinfo, t_list *env_list)
{
	if (check_dollar(quotinfo->cmdinfo->cmd))
	{
		quotinfo->new_cmd
			= hanlding_dollar(quotinfo->cmdinfo->cmd, env_list);
		if (quotinfo->cmdinfo->cmd)
			free(quotinfo->cmdinfo->cmd);
		quotinfo->cmdinfo->cmd = quotinfo->new_cmd;
	}
}

t_list	*part_nq(char *cmd, t_list *env_list, t_quotinfo *quotinfo)
{
	quotinfo->len = 0;
	while (cmd[quotinfo->i + quotinfo->len]
		&& cmd[quotinfo->i + quotinfo->len] != '\''
		&& cmd[quotinfo->i + quotinfo->len] != '"'
		&& cmd[quotinfo->i + quotinfo->len] != ' ')
		++quotinfo->len;
	quotinfo->cmdinfo = creat_cmdinfo();
	quotinfo->cmdinfo->cmd = ft_substr(cmd, quotinfo->i, quotinfo->len);
	parser_dollar(quotinfo, env_list);
	quotinfo->i = quotinfo->i + quotinfo->len;
	check_status(cmd[quotinfo->i], quotinfo);
	ft_lstadd_back(&quotinfo->list1, ft_lstnew((void *)quotinfo->cmdinfo));
	if (cmd[quotinfo->i] == '\0')
		return (quotinfo->list1);
	return (NULL);
}

t_list	*part_sq(char *cmd, t_quotinfo *quotinfo)
{
	if (cmd[quotinfo->i] == '\'')
	{
		quotinfo->cmdinfo = creat_cmdinfo();
		quotinfo->cmdinfo->cmd = ft_strdup("");
		check_status(cmd[quotinfo->i + 1], quotinfo);
		ft_lstadd_back(&quotinfo->list1, ft_lstnew((void *)quotinfo->cmdinfo));
		if (cmd[quotinfo->i] == '\0')
			return (quotinfo->list1);
	}
	else
	{
		quotinfo->len = 0;
		while (cmd[quotinfo->i + quotinfo->len]
			&& cmd[quotinfo->i + quotinfo->len] != '\'')
			++quotinfo->len;
		quotinfo->cmdinfo = creat_cmdinfo();
		quotinfo->cmdinfo->cmd = ft_substr(cmd, quotinfo->i, quotinfo->len);
		quotinfo->i = quotinfo->i + quotinfo->len;
		check_status(cmd[quotinfo->i + 1], quotinfo);
		ft_lstadd_back(&quotinfo->list1, ft_lstnew((void *)quotinfo->cmdinfo));
		if (cmd[quotinfo->i] == '\0')
			return (quotinfo->list1);
	}
	return (NULL);
}

t_list	*part_dq(char *cmd, t_list *env_list, t_quotinfo *quotinfo)
{
	if (cmd[quotinfo->i] == '"')
	{
		quotinfo->cmdinfo = creat_cmdinfo();
		quotinfo->cmdinfo->cmd = ft_strdup("");
		check_status(cmd[quotinfo->i + 1], quotinfo);
		ft_lstadd_back(&quotinfo->list1, ft_lstnew((void *)quotinfo->cmdinfo));
		if (cmd[quotinfo->i] == '\0')
			return (quotinfo->list1);
	}
	else
	{
		quotinfo->len = 0;
		while (cmd[quotinfo->i + quotinfo->len]
			&& cmd[quotinfo->i + quotinfo->len] != '"')
			++quotinfo->len;
		quotinfo->cmdinfo = creat_cmdinfo();
		quotinfo->cmdinfo->cmd = ft_substr(cmd, quotinfo->i, quotinfo->len);
		parser_dollar(quotinfo, env_list);
		quotinfo->i = quotinfo->i + quotinfo->len;
		check_status(cmd[quotinfo->i + 1], quotinfo);
		ft_lstadd_back(&quotinfo->list1, ft_lstnew((void *)quotinfo->cmdinfo));
		if (cmd[quotinfo->i] == '\0')
			return (quotinfo->list1);
	}
	return (NULL);
}
