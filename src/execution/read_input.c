/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:48:24 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/21 10:59:18 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms	g_ms;

void	interrupt_read(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(g_ms.stdin_rdl);
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

void	ft_readline(int fd, char *delimiter)
{
	int		len;

	len = ft_strlen(delimiter);
	signal(SIGINT, interrupt_read);
	while (1)
	{
		g_ms.stdin_rdl = readline("> ");
		if (!g_ms.stdin_rdl)
			exit_child(&g_ms, 1);
		if (!ft_strncmp(g_ms.stdin_rdl, delimiter, len))
		{
			free(g_ms.stdin_rdl);
			exit_child(&g_ms, 0);
		}
		ft_putendl_fd(g_ms.stdin_rdl, fd);
		free(g_ms.stdin_rdl);
		g_ms.stdin_rdl = NULL;
	}
	exit_child(&g_ms, 0);
}

int	read_from_current_input(t_ms *ms, char *delimiter)
{
	int		fd;
	int		pid;
	int		status;

	status = 0;
	fd = ft_open("tmp/heredoc.txt", O_RDWR | O_TRUNC | O_CREAT, 0666, ms);
	pid = ft_fork(ms);
	if (!pid)
		ft_readline(fd, delimiter);
	else
	{
		wait(&status);
		status = WEXITSTATUS(status);
	}
	check_read(&status, delimiter);
	close(fd);
	fd = ft_open("tmp/heredoc.txt", O_RDONLY, 0, ms);
	ft_dup2(fd, STDIN_FILENO, ms);
	close(fd);
	return (status);
}
