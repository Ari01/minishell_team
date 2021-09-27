/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:55:53 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/27 20:08:53 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int		is_flag(char c)
{
	return (c == '|' || c == '<' || c == '>');
}


int		get_flag(char *s)
{
	if (!is_flag(*s))
		return (0);
	if (*s == '<' && (*(s + 1) == '<'))
		return (DLR);
	if (*s == '>' && (*(s + 1) == '<'))
		return (DRR);
	return (*s);
}

int		check_rdl(t_ms *ms)
{
	if (ms->rdl[0] == '|')
	{
		printf("parsing error\n");
		free_memory(ms);
		return (0);
	}
	if (!ms->cmd_list_ite)
		return (0);
	return (1);
}
t_cmd	*init_cmd(void)
{
	t_cmd *cmd = NULL;

	cmd = malloc(sizeof(t_cmd));
	if (cmd){
		cmd->cmd = NULL;
		cmd->flag = 0;
	}
	return (cmd);
}
t_list	*get_cmds(char *s, t_ms ms)
{
	t_list	*cmd_list;
	t_cmd	*ctmp;
	char	*tmp;
	int		start;
	int		i;

	i = 0;
	cmd_list = NULL;
	ctmp = NULL;
	while (s[i])
	{
		start = i;
		i = check_flag(s, i);
		tmp = ft_substr(s, start, i - start); //截断一个pipe 获取里面的cmd 放进数组里
		ctmp = init_cmd();
		ctmp->cmd = lst_to_tab(tmp);
		ctmp->flag = get_flag(&s[i]);
		free(tmp);
		tmp = NULL;
		if (ctmp->flag == DLR || ctmp->flag == DRR)
			i++;
		
		ft_lstadd_back(&cmd_list, ft_lstnew(ctmp));
		i++;
	}
	return (cmd_list);
}

