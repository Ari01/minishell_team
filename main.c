/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:41 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/22 16:41:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	init_shell(char **env)
{
	t_ms	ms;

	ms.env_list = NULL;
	ms.env_list = get_env(env, ms.env_list);
	ms.history = init_history(ms.history);
	ms.cmd_list_head = NULL;
	ms.cmd_list_ite = NULL;
	return (ms);
}

void	run_context(t_ms *ms)
{
	t_cmd	current_cmd;

	current_cmd = *(t_cmd *)ms->cmd_list_ite->content;
	while (current_cmd.flag == SLR || current_cmd.flag == DLR
		|| current_cmd.flag == SRR || current_cmd.flag == DRR)
		redirect(ms, &current_cmd);
	printf("current command = %s\n", current_cmd.cmd[0]);
	if (current_cmd.cmd[0])
	{
		if (current_cmd.flag == '|')
			run_pipe(ms);
		else
			run_cmd(ms, &current_cmd);
	}
}

void	run_shell(char **env)
{
	t_ms	ms;
	t_list	*token_list;
	char	*check;

	ms = init_shell(env);
    while (1)
    {
        ms.rdl = readline("prompt> ");
		token_list = get_tokens(ms.rdl);
		check = check_grammar(token_list);

		t_token	token;
		while (token_list)
		{
			token = *(t_token *)token_list->content;
			printf("token = %s\n", token.value);
			token_list = token_list->next;
		}
		if (check)
		{
			printf("parse error near %s\n", check);
			free(ms.rdl);
			ms.rdl = NULL;
		}
		else
		{
			ms.cmd_list_head = get_cmds(ms.rdl);
			//get_stream(&ms.cmd_list_head);
			ms.cmd_list_ite = ms.cmd_list_head;
			//print_cmds(ms.cmd_list_ite);
			/*ms.fd_in = dup(STDIN_FILENO);
			ms.fd_out = dup(STDOUT_FILENO);
			//ft_add_history(ms.rdl, ms.history);
			if (ms.cmd_list_ite)
				run_context(&ms);
			free_memory(&ms);
			reset_fdin_fdout(&ms);*/
		}
    }
}

void printcmd(t_cmd *cmd) {
    int i =0;
    
    if (cmd) {
        printf("-- -- --\n");
        while (cmd->cmd && cmd->cmd[i]) {
            printf("cmd: [%s]\n", cmd->cmd[i++]);
        }
        printf("-- -- --\n");
    }
}

int		main(int ac, char **av, char **env) {
	(void)ac;
	(void)av;
	run_shell(env);
    return 0;
}
