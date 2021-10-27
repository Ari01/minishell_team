/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:36:07 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/27 15:14:54 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_redirect_pipe(t_ms *ms)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ms->cmd_list_ite->content;
	dup_error_fd(ms);
	if (cmd->in_file)
		ft_dup2(ms->fd_in, STDIN_FILENO, ms);
	ft_dup2(ms->fd_out, STDOUT_FILENO, ms);
	ms->cmd_ret = get_redirection(ms, cmd);
	ft_dup2(ms->fd_err, STDERR_FILENO, ms);
	if (ms->cmd_ret == 130)
	{
		ms->cmd_list_ite = NULL;
		return (1);
	}
	return (0);
}
