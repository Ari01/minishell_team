/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:12:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/17 17:49:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_ms *ms, int *pipe_fd)
{
	t_cmd	cmd;

	ms->cmd_list_ite = ms->cmd_list_ite->next;
	cmd = *(t_cmd*)ms->cmd_list_ite->content;
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	close(pipe_fd[0]);
	if (cmd.flag == '|')
		run_pipe(ms);
	else
	{
		if (cmd.flag == SLR || cmd.flag == DLR
			|| cmd.flag == SRR || cmd.flag == DRR)
			redirect(ms, &cmd);
		run_cmd(ms, &cmd);
	}
	exit(EXIT_SUCCESS);
}

void	exec_parent(t_ms *ms, int *pipe_fd, int pid)
{
	t_cmd	cmd;

	cmd = *(t_cmd *)ms->cmd_list_ite->content;
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	close(pipe_fd[1]);
	run_cmd(ms, &cmd);
	reset_fdin_fdout(ms);
	waitpid(pid, NULL, 0);
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
		exec_child(ms, pipe_fd);
	else
		exec_parent(ms, pipe_fd, pid);
}
