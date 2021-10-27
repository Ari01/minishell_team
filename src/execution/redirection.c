/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:50:32 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/26 15:18:01 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_in_out(char *stream, int flags)
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
	close(fd);
	return (0);
}

int	get_redirect_in(t_ms *ms, t_cmd *current_cmd)
{
	int		ret;
	t_io	*io;

	ret = 0;
	while (current_cmd->in_streams)
	{
		io = (t_io *)current_cmd->in_streams->content;
		if (io->flag == SLR && !ret)
		{
			ret = open_in_out(io->file, O_RDONLY);
			if (!current_cmd->in_streams->next)
				current_cmd->in_file = io->file;
		}
		else if (io->flag == DLR)
		{
			ret = read_from_current_input(ms, ret, io->file);
			signal(SIGINT, ft_interrupt);
			if (ret == 130)
				break ;
			if (!current_cmd->in_streams->next)
				current_cmd->in_file = "tmp/heredoc.txt";
		}
		current_cmd->in_streams = current_cmd->in_streams->next;
	}
	return (ret);
}

int	get_redirect_out(t_cmd *current_cmd)
{
	int		ret;
	t_io	*io;

	ret = 0;
	while (current_cmd->out_streams)
	{
		io = (t_io *)current_cmd->out_streams->content;
		if (io->flag == SRR)
			current_cmd->out_flags = O_RDWR | O_CREAT | O_TRUNC;
		else if (io->flag == DRR)
			current_cmd->out_flags = O_RDWR | O_CREAT | O_APPEND;
		ret = open_in_out(io->file, current_cmd->out_flags);
		if (ret)
			break ;
		if (!current_cmd->out_streams->next)
			current_cmd->out_file = io->file;
		current_cmd->out_streams = current_cmd->out_streams->next;
	}
	return (ret);
}

void	redirect(t_ms *ms, t_cmd *cmd)
{
	int	fd;

	if (cmd->in_file)
	{
		printf("infile = %s\n", cmd->in_file);
		fd = ft_open(cmd->in_file, O_RDONLY, 0, ms);
		ft_dup2(fd, STDIN_FILENO, ms);
		close(fd);
	}
	if (cmd->out_file)
	{
		printf("outfile = %s\n", cmd->out_file);
		fd = ft_open(cmd->out_file, cmd->out_flags, 0666, ms);
		ft_dup2(fd, STDOUT_FILENO, ms);
		close(fd);
	}
}

int	get_redirection(t_ms *ms, t_cmd *current_cmd)
{
	int		ret;

	ret = 0;
	if (current_cmd->in_stream_head)
		ret = get_redirect_in(ms, current_cmd);
	if (!ret && current_cmd->out_streams_head)
		ret = get_redirect_out(current_cmd);
	return (ret);
}
