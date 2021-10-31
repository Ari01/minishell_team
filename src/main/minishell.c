/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:19:47 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/31 18:14:04 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	g_ms;

t_ms	get_file_paths()
{
	t_ms	ms;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(0);
	}
	ms.error_file_path = ft_strjoin(tmp, "/tmp/error_file.txt");
	ms.heredoc_file_path = ft_strjoin(tmp, "/tmp/heredoc.txt");
	free(tmp);
	return (ms);
}

t_ms	init_shell(void)
{
	t_ms	ms;

	ms = get_file_paths();
	ms.fd_in = dup(STDIN_FILENO);
	ms.fd_out = dup(STDOUT_FILENO);
	ms.fd_err = dup(STDERR_FILENO);
	ms.cmd_ret = 0;
	ms.env_list = NULL;
	ms.history = init_history(ms.history);
	ms.cmd_list_head = NULL;
	ms.cmd_list_ite = NULL;
	return (ms);
}

int	run_simple_cmd(t_ms *ms, t_cmd *current_cmd)
{
	int	ret;

	init_error_fd(ms);
	dup_error_fd(ms);
	ret = redirect(ms, current_cmd);
	ft_dup2(ms->fd_err, STDERR_FILENO, ms);
	if (ret)
	{
		read_error(ms);
		return (ret);
	}
	if (current_cmd->cmd[0])
		ret = run_cmd(ms, current_cmd);
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
		if (current_cmd->flag == '|')
			ret = run_pipe(ms);
		else
		{
			ret = run_simple_cmd(ms, current_cmd);	
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
			reset_fds(&g_ms);
		}
	}
}
