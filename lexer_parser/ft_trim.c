/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:16:52 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/07 19:24:11 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_trim(t_list *cmd_list)
{
	t_list	*ite;
	t_cmd	*cmd;
	char	*freeptr;
	int		i;

	i = 0;
	ite = cmd_list;
	while (ite)
	{
		cmd = (t_cmd *)ite->content;
		while (cmd->cmd[i])
		{
			freeptr = cmd->cmd[i];
			cmd->cmd[i] = ft_strtrim(cmd->cmd[i], " \t\v\f\r");
			free(freeptr);
			i++;
		}
		ite = ite->next;
	}
	return (cmd_list);
}
