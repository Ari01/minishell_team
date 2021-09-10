/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:12:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/10 17:26:07 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_list *cmd_list, t_cmd cmd, int *pipe_fd)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR);
	if (cmd.flag == '|')
		run_pipe(cmd_list->next);
	else
		run_cmd(&cmd);
	close(pipe_fd[0]);
	exit(EXIT_SUCCESS);
}

void	exec_parent(t_cmd cmd, int *pipe_fd)
{
	int	status;

	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR);
	run_cmd(&cmd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(&status);
}

void	run_pipe(t_list *cmd_list)
{
	int		pid;
	int		pipe_fd[2];
	t_cmd	current_cmd;
	t_cmd	next_cmd;

	current_cmd = *(t_cmd*)cmd_list->content;
	if (cmd_list->next == NULL)
		print_error_msg("syntax error : expected cmd after '|'", SYNTAX_ERR);
	next_cmd = *(t_cmd*)cmd_list->next->content;
	if (pipe(pipe_fd) == -1)
		print_error_msg(strerror(errno), PIPE_ERR);
	pid = fork();
	if (!pid)
		exec_child(cmd_list, next_cmd, pipe_fd);
	else
		exec_parent(current_cmd, pipe_fd);
}
