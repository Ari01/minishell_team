/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:12:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/27 15:16:39 by dchheang         ###   ########.fr       */
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
	if (ms->cmd_ret)
		return (ms->cmd_ret);
	else
		read_error(ms);
	return (ret);
}

void	exec_child(t_ms *ms, int pipe_fd[2][2], int i, int npipe)
{
	t_cmd	*cmd;
	int		signal;

	cmd = (t_cmd *)ms->cmd_list_ite->next->content;
	close(pipe_fd[0][1]);
	signal = get_redirection(ms, cmd);
	if (!signal)
	{
		dup_error_fd(ms);
		redirect(ms, cmd);
		if (!cmd->in_file)
			ft_dup2(pipe_fd[0][0], STDIN_FILENO, ms);
		if (!cmd->out_file && i != npipe - 1)
			ft_dup2(pipe_fd[1][1], STDOUT_FILENO, ms);
		signal = run_cmd(ms, cmd);
	}
	close(pipe_fd[0][0]);
	close(pipe_fd[1][0]);
	close(pipe_fd[1][1]);
	exit_child(ms, signal);
}

void	exec_parent(t_ms *ms, int pipe_fd[2][2], int i, int npipe)
{
	t_cmd	*cmd;
	int		ret;

	ret = 0;
	cmd = (t_cmd *)ms->cmd_list_ite->content;
	close(pipe_fd[1][1]);
	if (!ms->cmd_ret)
	{
		redirect(ms, cmd);
		if (!cmd->out_file && i != npipe - 1)
			ft_dup2(pipe_fd[0][1], STDOUT_FILENO, ms);
		run_cmd(ms, cmd);
	}
	ft_dup2(pipe_fd[1][0], STDIN_FILENO, ms);
	close(pipe_fd[0][0]);
	close(pipe_fd[1][0]);
}

int	run_pipe(t_ms *ms)
{
	int		pid;
	int		pipe_fd[2][2];
	int		i;
	int		npipe;
	int		ret;

	i = 0;
	npipe = get_npipe(ms);
	init_error_fd(ms);
	ret = 0;
	while (i < npipe)
	{
		if (init_redirect_pipe(ms))
			break;
		ft_pipe(pipe_fd[0], ms);
		ft_pipe(pipe_fd[1], ms);
		pid = ft_fork(ms);
		if (!pid)
			exec_child(ms, pipe_fd, i, npipe);
		else
			exec_parent(ms, pipe_fd, i, npipe);
		i++;
		ms->cmd_list_ite = ms->cmd_list_ite->next->next;
	}
	return (wait_for_all(ms, i, pid));
}
