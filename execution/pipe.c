/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:12:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/30 19:54:08 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_ms *ms, int pipe_fd)
{
	t_cmd	cmd;

	ms->cmd_list_ite = ms->cmd_list_ite->next;
	cmd = *(t_cmd*)ms->cmd_list_ite->content;
	if (dup2(pipe_fd, STDIN_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	if (cmd.flag == '|')
		run_pipe(ms);
	else
	{
		if (cmd.in_stream.flag || cmd.out_streams)
			redirect(ms, &cmd);
		run_cmd(ms, &cmd);
	}
}

void	exec_parent(t_ms *ms, int pipe_fd)
{
	t_cmd	cmd;

	cmd = *(t_cmd *)ms->cmd_list_ite->content;
	if (dup2(pipe_fd, STDOUT_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	run_cmd(ms, &cmd);
	//reset_fdin_fdout(ms);
}

void	run_pipe(t_ms *ms)
{
	int		pid;
	int		pipe_fd[2];

	if (ms->cmd_list_ite->next == NULL)
		print_error_msg("syntax error : expected cmd after '|'", SYNTAX_ERR, ms);
	if (pipe(pipe_fd) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	pid = fork();
	if (!pid)
	{
		close(pipe_fd[1]);
		exec_child(ms, pipe_fd[0]);
		close(pipe_fd[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		exec_parent(ms, pipe_fd[1]);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	waitpid(pid, NULL, 0);
}
