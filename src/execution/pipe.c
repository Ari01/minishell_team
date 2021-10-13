/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:12:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/13 10:03:16 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_child(t_ms *ms, int pipe_fd)
{
	t_cmd	cmd;

	cmd = *(t_cmd *)ms->cmd_list_ite->content;
	if (cmd.in_streams || cmd.out_streams)
		redirect(ms, &cmd);
	if (!cmd.out_streams_head)
	{
		if (dup2(pipe_fd, STDOUT_FILENO) == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
		close(pipe_fd);
	}
	return (run_cmd(ms, &cmd));
}

int	run_pipe(t_ms *ms)
{
	int		pid;
	int		pipe_fd[2];
	int		signal;

	if (pipe(pipe_fd) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	pid = fork();
	if (!pid)
	{
		close(pipe_fd[0]);
		exit(exec_child(ms, pipe_fd[1]));
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, &signal, 0);
		if (dup2(ms->fd_out, STDOUT_FILENO) == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
		close(pipe_fd[0]);
	}
	return (signal);
}
