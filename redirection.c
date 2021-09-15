/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:50:32 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/15 19:24:44 by dchheang         ###   ########.fr       */
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

void	redirect_in_out(t_ms *ms, int newfd, int flags)
{
	int		fd;
	t_cmd	next_cmd;

	if (ms->cmd_list_ite->next == NULL)
		print_error_msg("missing argument after redirection\n", SYNTAX_ERR, ms);
	next_cmd = *(t_cmd *)ms->cmd_list_ite->next->content;
	if (flags & O_CREAT)
		fd = open(next_cmd.cmd[0], flags, 0666);
	else
		fd = open(next_cmd.cmd[0], flags);
	if (fd == -1)
		print_error_msg(strerror(errno), FILE_ERR, ms);
	if (dup2(fd, newfd) == -1)
		print_error_msg(strerror(errno), PIPE_ERR, ms);
	close(fd);
}

void	read_from_current_input(t_ms *ms)
{
	int		rd;
	char	buff[BUFFER_SIZE];
	char	*line;
	char	*freeptr;
	t_cmd	next_cmd;

	line = ft_strdup("");
	if (ms->cmd_list_ite->next == NULL)
		print_error_msg("missing argument after redirection\n", SYNTAX_ERR, ms);
	next_cmd = *(t_cmd *)ms->cmd_list_ite->next->content;
	rd = read(STDIN_FILENO, buff, BUFFER_SIZE - 1);
	buff[rd] = 0;
	while (ft_strncmp(buff, next_cmd.cmd[0], rd - 1) && rd != -1)
	{
		buff[rd] = 0;
		freeptr = line;
		line = ft_strjoin(line, buff);
		free(freeptr);
		rd = read(STDIN_FILENO, buff, BUFFER_SIZE - 1);
	}
	if (rd == -1)
		print_error_msg(strerror(errno), READ_WRITE_ERR, ms);
}

void	redirect(t_ms *ms, t_cmd *current_cmd)
{
	t_cmd	next_cmd;

	if (current_cmd->flag == SLR)
		redirect_in_out(ms, STDIN_FILENO, O_RDWR);
	else if (current_cmd->flag == SRR)
		redirect_in_out(ms, STDOUT_FILENO, O_RDWR | O_CREAT | O_TRUNC);
	else if (current_cmd->flag == DRR)
		redirect_in_out(ms, STDOUT_FILENO, O_RDWR | O_CREAT | O_APPEND);
	else
		read_from_current_input(ms);
	if (!current_cmd->cmd[0])
	{
		ms->cmd_list_ite = ms->cmd_list_ite->next;
		current_cmd = (t_cmd *)ms->cmd_list_ite->content;
		remove_elem_from_array(current_cmd->cmd);
	}
	else
	{
		next_cmd = *(t_cmd *)ms->cmd_list_ite->next->content;
		current_cmd->flag = next_cmd.flag;
		remove_from_list(&ms->cmd_list_head, ms->cmd_list_ite->next);
	}
}
