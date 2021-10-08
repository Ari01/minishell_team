/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:41 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/07 19:26:15 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	init_shell(char **env)
{
	t_ms	ms;

	ms.fd_in = dup(STDIN_FILENO);
	ms.fd_out = dup(STDOUT_FILENO);
	ms.env_list = NULL;
	ms.env_list = get_env(env, ms.env_list);
	ms.history = init_history(ms.history);
	ms.cmd_list_head = NULL;
	ms.cmd_list_ite = NULL;
	ms.cmd_ret = -1;
	return (ms);
}

int	run_context(t_ms *ms)
{
	t_cmd	*current_cmd;
	int		pid;
	int		ret;

	ret = 0;
	while (ms->cmd_list_ite)
	{
		current_cmd = (t_cmd *)ms->cmd_list_ite->content;
		if (current_cmd->in_streams || current_cmd->out_streams)
			redirect(ms, current_cmd);
		if (current_cmd->flag == '|')
			ret = ms->cmd_ret = run_pipe(ms);
		else if (current_cmd->cmd[0])
		{
			pid = fork();
			if (!pid)
			{
				ret = run_cmd(ms, current_cmd);
				//printf("rettt = %d\n", ret);
				exit(ret >> 8);
			}
			else
			{
				wait(&ret);
				ret = ret >> 8;
				//printf("ret = %d\n", ret);
			}
		}
		ms->cmd_list_ite = ms->cmd_list_ite->next;
	}
	return (ret);
}

void	run_shell(char **env)
{
	t_ms	ms;
	t_list	*token_list;
	char	*check;

	ms = init_shell(env);
    while (1)
    {
		ms.rdl = readline("prompt> ");  //取得一行数据line("prompt> ");
		if (!ms.rdl) {
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
		token_list = NULL;
		token_list = get_tokens(ms.rdl);
		check = check_grammar(token_list);
		ft_lstclear(&token_list, &free_token);
		if (check)
		{
			printf("parse error near %s\n", check);
			free(ms.rdl);
			ms.rdl = NULL;
		}
		else
		{
			ms.cmd_list_head = get_cmds(ms.rdl, ms.env_list, &ms);
			//ms.cmd_list_head = ft_trim(ms.cmd_list_head);
			ms.cmd_list_head = get_stream(ms.cmd_list_head);
			ms.cmd_list_ite = ms.cmd_list_head;
			print_cmds(ms.cmd_list_ite);
			ft_add_history(ms.rdl, ms.history);
			if (ms.cmd_list_ite)
				ms.cmd_ret = run_context(&ms);
			//free_memory(&ms);
			reset_fdin_fdout(&ms);
		}
    }
}

int		main(int ac, char **av, char **env) {
	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);  //crtl -\   /* ignore signal */
	signal(SIGINT,  ft_interrupt);
	run_shell(env);
    return 0;
}
