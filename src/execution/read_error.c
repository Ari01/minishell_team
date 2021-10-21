/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:07:07 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/21 10:47:55 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_error(int error_fd, t_ms *ms)
{
	char	buff[BUFFER_SIZE];
	int		rd;

	close(error_fd);
	error_fd = ft_open("tmp/error_file.txt", O_RDONLY, 0, ms);
	rd = read(error_fd, buff, BUFFER_SIZE - 1);
	while (rd > 0)
	{
		write(STDERR_FILENO, buff, rd);
		rd = read(error_fd, buff, BUFFER_SIZE - 1);
	}
	close(error_fd);
}
