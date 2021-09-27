/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:50:32 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/27 17:41:03 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_fdin_fdout(t_ms *ms)
{
	dup2(ms->fd_in, STDIN_FILENO);
	dup2(ms->fd_out, STDOUT_FILENO);
	close(ms->fd_in);
	close(ms->fd_out);
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
	char	buff[BUFFER_SIZE];

	fd = open("./tmp/heredoc.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		print_error_msg(strerror(errno), READ_WRITE_ERR, ms);
	rd = read(STDIN_FILENO, buff, BUFFER_SIZE - 1);
	while (ft_strncmp(buff, delimiter, rd - 1) && rd != -1)
	{
		write(fd, buff, rd);
		rd = read(STDIN_FILENO, buff, BUFFER_SIZE - 1);
	}
	close(fd);
	fd = open("./tmp/heredoc.txt", O_RDWR | O_CREAT, 0666);
	if (rd == -1 || fd == -1 || dup2(fd, STDIN_FILENO) == -1)
		print_error_msg(strerror(errno), READ_WRITE_ERR, ms);
	close(fd);
}

void	redirect(t_ms *ms, t_cmd *current_cmd)
{
	if (current_cmd->io_flag == SLR)
		redirect_in_out(ms, current_cmd->in_file, STDIN_FILENO, O_RDWR);
	else if (current_cmd->io_flag == DLR)
		read_from_current_input(ms, current_cmd->in_file);
	if (current_cmd->io_flag == SRR)
		redirect_in_out(ms, current_cmd->out_file, STDOUT_FILENO, O_RDWR | O_CREAT | O_TRUNC);
	else if (current_cmd->io_flag == DRR)
		redirect_in_out(ms, current_cmd->out_file, STDOUT_FILENO, O_RDWR | O_CREAT | O_APPEND);
}
