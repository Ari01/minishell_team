/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:50:32 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/13 10:05:25 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_fdin_fdout(t_ms *ms)
{
	dup2(ms->fd_in, STDIN_FILENO);
	dup2(ms->fd_out, STDOUT_FILENO);
}

void	redirect_in_out(t_ms *ms, char *stream, int newfd, int flags)
{
	int		fd;

	if (flags & O_CREAT)
		fd = open(stream, flags, 0666);
	else
		fd = open(stream, flags);
	if (fd == -1)
		print_error_msg(strerror(errno), FILE_ERR, ms);
	if (dup2(fd, newfd) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	close(fd);
}

void	read_from_current_input(t_ms *ms, char *delimiter)
{
	int		rd;
	int		fd;
	int		len;
	char	buff[BUFFER_SIZE];

	len = ft_strlen(delimiter);
	fd = open("./tmp/heredoc.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		print_error_msg(strerror(errno), READ_WRITE_ERR, ms);
	write(STDOUT_FILENO, "> ", 2);
	rd = read(ms->fd_in, buff, BUFFER_SIZE - 1);
	while (ft_strncmp(buff, delimiter, len) && rd > 0)
	{
		write(STDOUT_FILENO, "> ", 2);
		write(fd, buff, rd);
		rd = read(ms->fd_in, buff, BUFFER_SIZE - 1);
	}
	close(fd);
	fd = open("./tmp/heredoc.txt", O_RDWR | O_CREAT, 0666);
	if (rd == -1 || fd == -1 || dup2(fd, STDIN_FILENO) == -1)
		print_error_msg(strerror(errno), READ_WRITE_ERR, ms);
	close(fd);
}

void	redirect(t_ms *ms, t_cmd *current_cmd)
{
	t_io	*io;

	while (current_cmd->in_streams)
	{
		io = (t_io *)current_cmd->in_streams->content;
		if (io->flag == SLR)
			redirect_in_out(ms, io->file, STDIN_FILENO, O_RDWR);
		else if (io->flag == DLR)
			read_from_current_input(ms, io->file);
		current_cmd->in_streams = current_cmd->in_streams->next;
	}
	while (current_cmd->out_streams)
	{
		io = (t_io *)current_cmd->out_streams->content;
		if (io->flag == SRR)
			redirect_in_out(ms,
				io->file, STDOUT_FILENO,
				O_RDWR | O_CREAT | O_TRUNC);
		else if (io->flag == DRR)
			redirect_in_out(ms,
				io->file,
				STDOUT_FILENO,
				O_RDWR | O_CREAT | O_APPEND);
		current_cmd->out_streams = current_cmd->out_streams->next;
	}
}