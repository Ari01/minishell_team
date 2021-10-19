/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:48:24 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/19 12:18:59 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt_read(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(130);
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
	msg = "minishell: avertissement : « here-document » à la ligne";
	if (*status == 1)
	{
		printf("%s %d délimité par la fin du fichier (au lieu de « %s »)\n",
			msg, nline, delimiter);
		*status = 0;
	}
}

void	ft_readline(int fd, char *delimiter)
{
	int		len;
	char	*rdl;

	len = ft_strlen(delimiter);
	signal(SIGINT, interrupt_read);
	while (1)
	{
		rdl = readline("> ");
		if (!rdl)
			exit(1);
		if (!ft_strncmp(rdl, delimiter, len))
		{
			free(rdl);
			exit(0);
		}
		ft_putendl_fd(rdl, fd);
		free(rdl);
		rdl = NULL;
	}
	exit(0);
}

int	read_from_current_input(t_ms *ms, char *delimiter)
{
	int		fd;
	int		pid;
	int		status;

	status = 0;
	fd = open("tmp/heredoc.txt", O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
		print_error_msg(strerror(errno), READ_WRITE_ERR, ms);
	pid = fork();
	if (pid == -1)
		print_error_msg(strerror(errno), READ_WRITE_ERR, ms);
	if (!pid)
		ft_readline(fd, delimiter);
	else
	{
		wait(&status);
		status = WEXITSTATUS(status);
	}
	check_read(&status, delimiter);
	close(fd);
	fd = open("tmp/heredoc.txt", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		print_error_msg(strerror(errno), READ_WRITE_ERR, ms);
	close(fd);
	return (status);
}
