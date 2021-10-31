/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:48:24 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/31 18:21:37 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms	g_ms;

void	interrupt_read(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(g_ms.stdin_rdl);
	g_ms.stdin_rdl = NULL;
	close(g_ms.open_fd);
	exit_child(&g_ms, 130);
}

int	get_nline(t_ms *ms)
{
	int		fd;
	int		rd;
	int		nline;
	char	*line;

	rd = 1;
	nline = 0;
	fd = ft_open(ms->heredoc_file_path, O_RDONLY, 0, ms);
	while (rd > 0)
	{
		rd = get_next_line(fd, &line);
		free(line);
		line = NULL;
		nline++;
	}
	if (rd == -1)
		print_error_msg(strerror(errno), errno, ms);
	close(fd);
	return (nline);
}

void	check_read(t_ms *ms, int *status, char *delimiter)
{
	char	*msg;
	int		nline;

	nline = get_nline(ms);
	msg = "minishell: warning: here-document at line ";
	if (*status == 1)
	{
		printf("%s %d delimited by end-of-file (wanted `%s')\n",
			msg, nline, delimiter);
		*status = 0;
	}
}

void	ft_readline(t_ms *ms, char *delimiter)
{
	int		len;

	ms->open_fd = ft_open(ms->heredoc_file_path,
			O_RDWR | O_TRUNC | O_CREAT, 0666, ms);
	len = ft_strlen(delimiter);
	signal(SIGINT, interrupt_read);
	while (1)
	{
		ms->stdin_rdl = readline("> ");
		if (!ms->stdin_rdl)
		{
			close(ms->open_fd);
			exit_child(ms, 1);
		}
		if (!ft_strncmp(ms->stdin_rdl, delimiter, len))
		{
			free(ms->stdin_rdl);
			ms->stdin_rdl = NULL;
			break ;
		}
		ft_putendl_fd(ms->stdin_rdl, ms->open_fd);
		free(ms->stdin_rdl);
	}
	close(ms->open_fd);
	exit_child(ms, 0);
}

int	read_from_current_input(t_ms *ms, int error, char *delimiter)
{
	int		fd;
	int		pid;
	int		status;

	pid = ft_fork(ms);
	if (!pid)
		ft_readline(ms, delimiter);
	else
	{
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	check_read(ms, &status, delimiter);
	if (!error)
	{
		fd = ft_open(ms->heredoc_file_path, O_RDONLY, 0, ms);
		ft_dup2(fd, STDIN_FILENO, ms);
		close(fd);
		return (status);
	}
	return (error);
}
