/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:12:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/17 07:02:02 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_npipe(t_ms *ms)
{
	t_cmd	*cmd;
	t_list	*ite;
	int		ret;

	ret = 0;
	ite = ms->cmd_list_ite;
	while (ite)
	{
		cmd = (t_cmd *)ite->content;
		if (cmd->flag != PIPE)
			break;
		ret++;
		ite = ite->next;
	}
	return (ret);
}

void	wait_for_all(t_ms *ms, int npipe)
{
	int	signal;
	int	i;

	i = 0;
	while (i < npipe)
	{
		wait(&signal);
		ms->cmd_ret = WEXITSTATUS(signal);
		i++;
	}
}

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
	}
	return (run_cmd(ms, &cmd));
}

int	run_pipe(t_ms *ms)
{
	int		pid;
	int		pipe_fd[2];
	int		signal;
	int		i;
	int		npipe;

	i = 0;
	signal = 0;
	npipe = get_npipe(ms);
	while (i < npipe)
	{
		if (pipe(pipe_fd) == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
		pid = fork();
		if (pid == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
		if (!pid)
		{
			signal = exec_child(ms, pipe_fd[1]);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(signal);
		}
		else
		{
			close(pipe_fd[1]);
			if (dup2(ms->fd_out, STDOUT_FILENO) == -1)
				print_error_msg(strerror(errno), PIPE_ERR, ms);
			if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
				print_error_msg(strerror(errno), PIPE_ERR, ms);
			close(pipe_fd[0]);
		}
		i++;
		ms->cmd_list_ite = ms->cmd_list_ite->next;
	}
	wait_for_all(ms, npipe);
	return (signal);
}
