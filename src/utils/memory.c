/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 09:26:45 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/18 09:43:14 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(content);
}

void	free_io(void *content)
{
	t_io	*io;

	io = (t_io *)content;
	free(io->file);
	free(io);
}

void	free_cmd(void *content)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = (t_cmd *)content;
	while (cmd->cmd[i])
	{
		free(cmd->cmd[i]);
		i++;
	}
	free(cmd->cmd);
	ft_lstclear(&cmd->out_streams_head, &free_io);
	ft_lstclear(&cmd->in_stream_head, &free_io);
	free(cmd);
}

void	free_memory(t_ms *ms)
{
	free(ms->rdl);
	ms->rdl = NULL;
	ft_lstclear(&ms->cmd_list_head, &free_cmd);
}
