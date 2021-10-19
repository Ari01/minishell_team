/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:09:30 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/04 17:04:15 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *env_list, t_cmd *cmd)
{
	if (!cmd || cmd->cmd[1] != NULL)
		return (ERROR);
	while (env_list)
	{
		if (ft_strchr((char *)env_list->content, '='))
		{
			print_msg((char *)env_list->content, "\n", NULL, STDOUT_FILENO);
		}
		env_list = env_list->next;
	}
	return (SUCCESS);
}
