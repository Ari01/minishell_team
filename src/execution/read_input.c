/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:48:24 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/22 08:03:20 by dchheang         ###   ########.fr       */
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

void	check_read(int *status, char *delimiter)
{
	char	*msg;
	char	*line;
	int		nline;
	int		fd;
	int		rd;

	nline = 0;
	fd = open("tmp/heredoc.txt", O_RDONLY);
	rd = 1;
	while (rd > 0)
	{
		rd = get_next_line(fd, &line);
		free(line);
		line = NULL;
		nline++;
	}
	close(fd);
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

	ms->open_fd = ft_open("tmp/heredoc.txt", O_RDWR | O_TRUNC | O_CREAT, 0666, ms);
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
			break;
		}
		ft_putendl_fd(ms->stdin_rdl, ms->open_fd);
		free(ms->stdin_rdl);
		ms->stdin_rdl = NULL;
	}
	close(ms->open_fd);
	exit_child(ms, 0);
}

int	read_from_current_input(t_ms *ms, char *delimiter)
{
	int		fd;
	int		pid;
	int		status;

	status = 0;
	pid = ft_fork(ms);
	if (!pid)
		ft_readline(ms, delimiter);
	else
	{
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	check_read(&status, delimiter);
	fd = ft_open("tmp/heredoc.txt", O_RDONLY, 0, ms);
	ft_dup2(fd, STDIN_FILENO, ms);
	close(fd);
	return (status);
}
