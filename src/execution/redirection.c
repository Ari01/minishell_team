/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:50:32 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/27 16:30:17 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in_out(t_ms *ms, char *stream, int newfd, int flags)
{
	int		fd;

	if (flags & O_CREAT)
		fd = open(stream, flags, 0666);
	else
		fd = open(stream, flags);
	if (fd == -1)
	{
		print_msg("minishell: ", stream, strerror(errno), STDERR_FILENO);
		return (1);
	}
	if (dup2(fd, newfd) == -1)
	{
		close(fd);
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	}
	close(fd);
	return (0);
}

int	redirect_in(t_ms *ms, t_cmd *current_cmd)
{
	int		ret;
	t_io	*io;

	ret = 0;
	while (current_cmd->in_streams)
	{
		io = (t_io *)current_cmd->in_streams->content;
		if (io->flag == SLR && !ret)
			ret = redirect_in_out(ms, io->file, STDIN_FILENO, O_RDWR);
		else if (io->flag == DLR)
		{
			ft_dup2(ms->fd_in, STDIN_FILENO, ms);
			ret = read_from_current_input(ms, ret, io->file);
			signal(SIGINT, ft_interrupt);
			if (ret == 130)
				break ;
			if (!current_cmd->in_streams->next)
				current_cmd->dlr = 1;
		}
		current_cmd->in_streams = current_cmd->in_streams->next;
	}
	return (ret);
}

int	redirect_out(t_ms *ms, t_cmd *current_cmd)
{
	int		ret;
	int		flags;
	t_io	*io;

	ret = 0;
	while (current_cmd->out_streams)
	{
		io = (t_io *)current_cmd->out_streams->content;
		if (io->flag == SRR)
			flags = O_RDWR | O_CREAT | O_TRUNC;
		else if (io->flag == DRR)
			flags = O_RDWR | O_CREAT | O_APPEND;
		ret = redirect_in_out(ms, io->file, STDOUT_FILENO, flags);
		if (ret)
			break ;
		current_cmd->out_streams = current_cmd->out_streams->next;
	}
	return (ret);
}

int	redirect_pipe(t_ms *ms)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ms->cmd_list_ite->content;
	dup_error_fd(ms);
	ms->cmd_ret = redirect(ms, cmd);
	ft_dup2(ms->fd_err, STDERR_FILENO, ms);
	if (ms->cmd_ret == 130)
	{
		ms->cmd_list_ite = NULL;
		return (1);
	}
	return (0);
}

int	redirect(t_ms *ms, t_cmd *current_cmd)
{
	int		ret;

	ret = 0;
	if (current_cmd->in_streams)
		ret = redirect_in(ms, current_cmd);
	if (!ret && current_cmd->out_streams)
		ret = redirect_out(ms, current_cmd);
	return (ret);
}
