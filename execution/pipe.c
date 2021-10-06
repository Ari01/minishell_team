/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:12:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/06 19:25:56 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_ms *ms, int pipe_fd)
{
	t_cmd	cmd;

	cmd = *(t_cmd*)ms->cmd_list_ite->content;
	if (cmd.in_streams || cmd.out_streams)
		redirect(ms, &cmd);
	if (!cmd.out_streams_head)
	{
		if (dup2(pipe_fd, STDOUT_FILENO) == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
		close(pipe_fd);
	}
	run_cmd(ms, &cmd);
}

void	run_pipe(t_ms *ms)
{
	int		pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	pid = fork();
	if (!pid)
	{
		close(pipe_fd[0]);
		exec_child(ms, pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		if (dup2(ms->fd_out, STDOUT_FILENO) == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
		close(pipe_fd[0]);
	}
}
