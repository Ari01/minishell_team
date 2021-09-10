/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:50:32 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/10 18:58:23 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(t_list *cmd_list)
{
	int		fd;
	t_cmd	current_cmd;
	t_cmd	next_cmd;

	fd = -1;
	current_cmd = *(t_cmd *)cmd_list->content;
	if (cmd_list->next == NULL)
		print_error_msg("missing filename after redirection\n", 1);
	next_cmd = *(t_cmd *)cmd_list->next->content;
	fd = open(next_cmd.cmd[0], O_RDONLY);
	if (fd == -1)
		print_error_msg(strerror(errno), FILE_ERR);
	if (dup2(fd, STDIN_FILENO) == -1)
		print_error_msg(strerror(errno), PIPE_ERR);
	remove_elem_from_array(next_cmd.cmd);
}
