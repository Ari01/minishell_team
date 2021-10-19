/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:01 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/07 17:52:02 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_echo
{
	int	i;
	int	n;
}t_echo;

static t_echo	init_echo(void)
{
	t_echo	echo;

	echo.i = 1;
	echo.n = 0;
	return (echo);
}

int	ft_echo(t_cmd *cmd)
{
	t_echo	echo;

	echo = init_echo();
	if (!cmd || !cmd->cmd[echo.i])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (ERROR);
	}
	if (!cmd->cmd[1])
		ft_putendl_fd("", STDOUT_FILENO);
	while (cmd && cmd->cmd[echo.i] && (ft_strcmp(cmd->cmd[echo.i], "-n") == 0))
	{
		echo.i++;
		echo.n = 1;
	}
	while (cmd && cmd->cmd[echo.i])
	{
		ft_putstr_fd(cmd->cmd[echo.i], STDOUT_FILENO);
		if (cmd->cmd[echo.i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		else if (!cmd->cmd[echo.i + 1] && echo.n == 0)
			ft_putstr_fd("\n", STDOUT_FILENO);
		echo.i++;
	}
	return (SUCCESS);
}
