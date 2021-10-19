/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:11:12 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/07 18:39:38 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strisdigit(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}

static int	check_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	if (!cmd)
		return (ERROR);
	else if (cmd && cmd->cmd[1] && cmd->cmd[2] && ft_strisdigit(cmd->cmd[1]))
	{
		print_msg ("exit\n", "prompt: exit: too many arguments\n",
			NULL, STDERR_FILENO);
		return (ERROR);
	}
	else if (cmd && cmd->cmd[1] && !(ft_strisdigit(cmd->cmd[1]))
		&& !check_nbr(cmd->cmd[1]))
	{
		print_msg("exit\nprompt: exit: ", cmd->cmd[1],
			": numeric argument required\n", STDERR_FILENO);
		exit(0);
	}
	else
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(0);
	}
}
