/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:19:47 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/20 07:41:45 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	g_ms;

t_ms	init_shell(void)
{
	t_ms	ms;

	ms.fd_in = dup(STDIN_FILENO);
	ms.fd_out = dup(STDOUT_FILENO);
	ms.env_list = NULL;
	ms.history = init_history(ms.history);
	ms.cmd_list_head = NULL;
	ms.cmd_list_ite = NULL;
	return (ms);
}

int	run_simple_cmd(t_ms *ms, t_cmd *current_cmd)
{
	int	pid;
	int	ret;

	pid = fork();
	if (!pid)
		exit(run_cmd(ms, current_cmd));
	else
	{
		waitpid(pid, &ret, 0);
		ret = WEXITSTATUS(ret);
	}
	return (ret);
}

int	run_context(t_ms *ms)
{
	t_cmd	*current_cmd;
	int		ret;

	ret = 0;
	while (ms->cmd_list_ite)
	{
		current_cmd = (t_cmd *)ms->cmd_list_ite->content;
		if (current_cmd->in_streams || current_cmd->out_streams)
			ret = redirect(ms, current_cmd);
		if (ret)
			break ;
		if (current_cmd->flag == '|')
			run_pipe(ms);
		else
		{
			if (current_cmd->cmd[0])
				ret = run_cmd(ms, current_cmd);
			ms->cmd_list_ite = ms->cmd_list_ite->next;
		}
	}
	return (ret);
}

void	run_shell(char **env)
{
	g_ms = init_shell();
	g_ms.env_list = get_env(env, g_ms.env_list);
	g_ms.envp = env;
	while (1)
	{
		g_ms.rdl = readline("prompt> ");
		if (!check_error(&g_ms))
		{
			g_ms.cmd_list_head = get_cmds(g_ms.rdl, g_ms.env_list);
			g_ms.cmd_list_head = get_stream(g_ms.cmd_list_head);
			g_ms.cmd_list_ite = g_ms.cmd_list_head;
			ft_add_history(g_ms.rdl, g_ms.history);
			if (g_ms.cmd_list_ite)
				g_ms.cmd_ret = run_context(&g_ms);
			free_memory(&g_ms);
			reset_fdin_fdout(&g_ms);
		}
	}
}
