/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:12:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/21 12:23:08 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms	g_ms;

int	get_npipe(t_ms *ms)
{
	t_cmd	*cmd;
	t_list	*ite;
	int		ret;

	ret = 1;
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

int	wait_for_all(t_ms *ms, int npipe, int last_pid)
{
	int	signal;
	int	i;
	int	ret;
	int	pid;

	i = 0;
	ret = 0;
	while (i < npipe)
	{
		pid = wait(&signal);
		if (pid == last_pid)
			ret = WEXITSTATUS(signal);
		i++;
	}
	ft_dup2(ms->fd_err, STDERR_FILENO, ms);
	read_error(ms);
	return (ret);
}

void	exec_child(t_ms *ms, int *pipe_fd, int i, int npipe)
{
	t_cmd	cmd;
	int		signal;

	cmd = *(t_cmd *)ms->cmd_list_ite->content;
	if (cmd.in_streams || cmd.out_streams)
		redirect(ms, &cmd);
	if (!cmd.out_streams_head && i != npipe - 1)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
	}
	signal = run_cmd(ms, &cmd);
	if (signal == 127)
		reset_fds(ms);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit_child(ms, signal);
}

void	exec_parent(t_ms *ms, int *pipe_fd, int i, int npipe)
{
	close(pipe_fd[1]);
	if (dup2(ms->fd_out, STDOUT_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	if (i != npipe - 1)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			print_error_msg(strerror(errno), PIPE_ERR, ms);
	}
	close(pipe_fd[0]);
}

int	run_pipe(t_ms *ms)
{
	int		pid;
	int		pipe_fd[2];
	int		error_fd;
	int		i;
	int		npipe;

	i = 0;
	npipe = get_npipe(ms);
	error_fd = ft_open("tmp/error_file.txt", O_RDWR | O_TRUNC | O_CREAT, 0666, ms);
	ft_dup2(error_fd, STDERR_FILENO, ms);
	close(error_fd);
	while (i < npipe)
	{
		ft_pipe(pipe_fd, ms);
		pid = ft_fork(ms);
		if (!pid)
			exec_child(ms, pipe_fd, i, npipe);
		else
			exec_parent(ms, pipe_fd, i, npipe);
		i++;
		ms->cmd_list_ite = ms->cmd_list_ite->next;
	}
	return (wait_for_all(ms, npipe, pid));
}
