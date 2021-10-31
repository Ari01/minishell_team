/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:15 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/31 18:18:41 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_home(t_list *env_list)
{
	t_list	*search;

	search = check_exist("HOME", env_list);
	if (!search)
	{
		print_msg("minishell: ", "cd", "HOME not set", STDERR_FILENO);
		return (ERROR);
	}
	else if (chdir(get_var(search, "HOME")) == -1)
		perror("minishell: cd: ");
	return (SUCCESS);
}

int	ft_cd(t_cmd *cmd, t_list *env_list)
{
	if (!cmd)
		return (ERROR);
	if (cmd && !cmd->cmd[1])
	{
		if (check_home(env_list) == ERROR)
			return (ERROR);
	}
	else if (cmd && cmd->cmd[1] != NULL)
	{
		if (chdir(cmd->cmd[1]) != -1)
			return (SUCCESS);
		else
		{
			print_msg("minishell: cd: ",
				cmd->cmd[1], strerror(errno), STDERR_FILENO);
			return (ERROR);
		}
	}
	return (SUCCESS);
}
