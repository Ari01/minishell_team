/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:15 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/11 14:53:49 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file(t_cmd *cmd)
{
	int			fd;
	const char	*path;

	path = cmd->cmd[1];
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	return (1);
}

static int	check_home(void)
{
	if (chdir(getenv("HOME")) == -1)
	{
		print_msg("cd: HOME not set\n", NULL, NULL, STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int	ft_cd(t_cmd *cmd)
{
	if (!cmd)
		return (ERROR);
	if (cmd && ! cmd->cmd[1])
	{
		if (check_home() == ERROR)
			return (ERROR);
	}
	else if (cmd && cmd->cmd[1] != NULL && !(check_file(cmd)))
	{
		print_msg("prompt: cd: ", cmd->cmd[1],
			": No such file or directory\n", STDERR_FILENO);
		return (ERROR);
	}
	else if (cmd && cmd->cmd[1] && check_file(cmd))
	{
		if (!chdir(cmd->cmd[1]))
			return (ERROR);
	}
	return (SUCCESS);
}
