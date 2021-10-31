/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:09:30 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/31 17:42:11 by dchheang         ###   ########.fr       */
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
			ft_putendl_fd((char *)env_list->content, STDOUT_FILENO);
		env_list = env_list->next;
	}
	return (SUCCESS);
}
