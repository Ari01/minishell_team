/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:28:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/17 04:07:30 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	creat_history(t_history *history)
{
	char	*home;
	char	*path;

	home = NULL;
	path = NULL;
	if (!home || (open(home, O_RDONLY) == -1))
	{
		if (home)
			free(home);
		home = getcwd(NULL, 0);
	}
	path = ft_strjoin(home, "/.minishell_history");
	free(home);
	history->path = path;
	history->fd = open(history->path, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (history->fd == -1)
		return ;
}

static void	add_exist_history(t_history *history)
{
	char	*line;
	int		read;

	read = 1;
	while (read > 0)
	{
		read = get_next_line(history->fd, &line);
		add_history(line);
		free(line);
		line = NULL;
	}
}

t_history	init_history(t_history history)
{
	creat_history(&history);
	add_exist_history(&history);
	return (history);
}

void	ft_add_history(char *cmd, t_history history)
{
	if (!cmd || !ft_strlen(cmd))
		return ;
	if ((open(history.path, O_RDONLY)) == -1)
	{
		history.fd = open(history.path, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (history.fd == -1)
			return ;
	}
	ft_putendl_fd(cmd, history.fd);
	add_history(cmd);
}
