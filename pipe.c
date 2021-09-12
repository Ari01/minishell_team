/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:12:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/11 17:33:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_ms *ms, t_list *cmd_list, int *pipe_fd)
{
	t_cmd cmd;

	cmd = *(t_cmd*)cmd_list->next->content;
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	if (cmd.flag == '|')
		run_pipe(ms, cmd_list->next);
	else
		run_cmd(&cmd);
	close(pipe_fd[0]);
	exit(EXIT_SUCCESS);
}

void	exec_parent(t_ms *ms, t_list *cmd_list, int *pipe_fd)
{
	int		status;
	t_cmd	cmd;

	cmd = *(t_cmd *)cmd_list->content;
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	run_cmd(&cmd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(&status);
}

void	run_pipe(t_ms *ms, t_list *cmd_list)
{
	int		pid;
	int		pipe_fd[2];
	t_cmd	current_cmd;
	t_cmd	next_cmd;

	current_cmd = *(t_cmd*)cmd_list->content;
	if (cmd_list->next == NULL)
		print_error_msg("syntax error : expected cmd after '|'", SYNTAX_ERR, ms);
	next_cmd = *(t_cmd*)cmd_list->next->content;
	if (pipe(pipe_fd) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	pid = fork();
	if (!pid)
		exec_child(ms, cmd_list, pipe_fd);
	else
		exec_parent(ms, cmd_list, pipe_fd);
}
