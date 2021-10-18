/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:50:32 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/18 10:44:03 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in_out(t_ms *ms, char *stream, int newfd, int flags)
{
	int		fd;
	char	*tmp;

	if (flags & O_CREAT)
		fd = open(stream, flags, 0666);
	else
		fd = open(stream, flags);
	if (fd == -1)
	{
		tmp = ft_strjoin("minishell: ", stream);
		perror(tmp);
		free(tmp);
		return (1);
	}
	if (dup2(fd, newfd) == -1)
	{
		close(fd);
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	}
	return (0);
}

void	read_from_current_input(t_ms *ms, char *delimiter)
{
	int		rd;
	int		len;
	char	buff[BUFFER_SIZE];
	int		nline;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	nline = 1;
	len = ft_strlen(delimiter);
	write(STDOUT_FILENO, "> ", 2);
	rd = read(ms->fd_in, buff, BUFFER_SIZE - 1);
	while (ft_strncmp(buff, delimiter, len) && rd > 0)
	{
		write(STDOUT_FILENO, "> ", 2);
		write(pipe_fd[1], buff, rd);
		nline++;
		rd = read(ms->fd_in, buff, BUFFER_SIZE - 1);
	}
	check_read_from_input(rd, nline, delimiter);
	close(pipe_fd[1]);
	if (rd == -1 || dup2(pipe_fd[0], STDIN_FILENO) == -1)
		print_error_msg(strerror(errno), READ_WRITE_ERR, ms);
	close(pipe_fd[0]);
}

int	redirect_in(t_ms *ms, t_cmd *current_cmd)
{
	int		ret;
	t_io	*io;

	ret = 0;
	while (current_cmd->in_streams)
	{
		io = (t_io *)current_cmd->in_streams->content;
		if (io->flag == SLR)
		{
			ret = redirect_in_out(ms, io->file, STDIN_FILENO, O_RDWR);
			if (ret)
				return (ret);
		}
		else if (io->flag == DLR)
			read_from_current_input(ms, io->file);
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

int	redirect(t_ms *ms, t_cmd *current_cmd)
{
	int		ret;

	ret = redirect_in(ms, current_cmd);
	if (!ret)
		ret = redirect_out(ms, current_cmd);
	return (ret);
}
