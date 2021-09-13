/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:41 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/13 16:47:04 by dchheang         ###   ########.fr       */
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
		redirect(ms, current_cmd);
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
		run_cmd(&current_cmd);
}

void	run_shell()
{
	t_ms	ms;

    while (1)
    {
        ms.rdl = readline("prompt> ");
		ms.cmd_list_head = get_cmds(ms.rdl);
		ms.cmd_list_ite = ms.cmd_list_head;
		ms.fd_in = dup(STDIN_FILENO);
		ms.fd_out = dup(STDOUT_FILENO);
		if (!ms.cmd_list_ite)
			print_error_msg("command not recognized\n", SYNTAX_ERR, &ms);
		run_context(&ms);
		reset_fdin_fdout(&ms);
		free_memory(&ms);
    }
}

int		main(void) {
	run_shell();
    return 0;
}
