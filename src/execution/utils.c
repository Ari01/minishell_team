/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:16:28 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/31 18:22:02 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open(char *path, int flags, int permissions, t_ms *ms)
{
	int	fd;

	if (permissions)
		fd = open(path, flags, permissions);
	else
		fd = open(path, flags);
	if (fd == -1)
		print_error_msg(strerror(errno), OPEN_ERR, ms);
	return (fd);
}

void	ft_pipe(int *pipe_fd, t_ms *ms)
{
	if (pipe(pipe_fd) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
}

void	ft_dup2(int oldfd, int newfd, t_ms *ms)
{
	if (dup2(oldfd, newfd) == -1)
		print_error_msg(strerror(errno), DUP_ERR, ms);
}

int	ft_fork(t_ms *ms)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	return (pid);
}
