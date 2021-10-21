/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:12:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/21 11:48:06 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms	g_ms;

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
			break ;
		ret++;
		ite = ite->next;
	}
	return (ret);
}

void	wait_for_all(t_ms *ms, int error_fd, int npipe)
{
	int	signal;
	int	i;

	i = 0;
	while (i < npipe)
	{
		wait(&signal);
		g_ms.cmd_ret = WEXITSTATUS(signal);
		i++;
	}
	ft_dup2(ms->fd_err, STDERR_FILENO);
	read_error()
}

void	exec_child(t_ms *ms, int *pipe_fd)
{
	t_cmd	cmd;
	int		signal;

	cmd = *(t_cmd *)ms->cmd_list_ite->content;
	if (cmd.in_streams || cmd.out_streams)
		redirect(ms, &cmd);
	if (!cmd.out_streams_head)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
	}
	signal = run_cmd(ms, &cmd);
	if (signal == 127)
		reset_fdin_fdout(ms);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit_child(ms, signal);
}

void	exec_parent(t_ms *ms, int *pipe_fd)
{
	close(pipe_fd[1]);
	if (dup2(ms->fd_out, STDOUT_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	close(pipe_fd[0]);
}

void	run_pipe(t_ms *ms)
{
	int		pid;
	int		pipe_fd[2];
	int		error_fd;
	int		i;
	int		npipe;

	i = 0;
	npipe = get_npipe(ms);
	error_fd = ft_open("tmp/error_file.txt", O_RDWR | O_TRUNC | O_CREAT, 0666, ms);
	ft_dup2(pipe_err, STDERR_FILENO)
	while (i < npipe)
	{
		if (pipe(pipe_fd) == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
		pid = fork();
		if (pid == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
		if (!pid)
			exec_child(ms, pipe_fd);
		else
			exec_parent(ms, pipe_fd);
		i++;
		ms->cmd_list_ite = ms->cmd_list_ite->next;
	}
	wait_for_all(ms, error_fd, npipe);
}
