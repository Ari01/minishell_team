/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:41 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/01 14:29:33 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_context(t_ms *ms)
{
	t_cmd	current_cmd;
	current_cmd = *(t_cmd *)ms->cmd_list_ite->content;
	if (current_cmd.flag == SLR || current_cmd.flag == DLR
		|| current_cmd.flag == SRR || current_cmd.flag == DRR)
	{
		redirect(ms, &current_cmd);
		if (!current_cmd.cmd[0])
		{
			ms->cmd_list_ite = ms->cmd_list_ite->next;
			current_cmd = *(t_cmd*)ms->cmd_list_ite->content;
			printf("cc = %s\n", current_cmd.cmd[0]);
		}
	}
	if (current_cmd.flag == '|')
		run_pipe(ms);
	else
		run_cmd(ms, &current_cmd);
}

void	run_shell(char **env)
{
	t_ms	ms;

	ms.env_list = NULL;
	ms.env_list = get_env(env, ms.env_list);
	ms.history = init_history(ms.history);
    while (1)
    {
        ms.rdl = readline("prompt> ");  //取得一行数据
		if (!ms.rdl) {
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
		ms.cmd_list_head = get_cmds(ms.rdl, ms.env_list); 
		ft_add_history(ms.rdl, ms.history);
		ms.cmd_list_ite = ms.cmd_list_head;
		ms.fd_in = dup(STDIN_FILENO);
		ms.fd_out = dup(STDOUT_FILENO);
		if (!ms.cmd_list_ite)
			print_error_msg("command not recognized\n", SYNTAX_ERR, &ms);
		run_context(&ms);
		reset_fdin_fdout(&ms);
		//free_memory(&ms);
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
