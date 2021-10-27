/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:53:02 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/27 16:22:08 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flag(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	get_flag(char *s)
{
	if (!is_flag(*s))
		return (0);
	if (*s == '<' && (*(s + 1) == '<'))
		return (DLR);
	if (*s == '>' && (*(s + 1) == '>'))
		return (DRR);
	return (*s);
}

int	check_rdl(t_ms *ms)
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
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->dlr = 0;
	cmd->in_streams = NULL;
	cmd->in_stream_head = NULL;
	cmd->out_streams = NULL;
	cmd->out_streams_head = NULL;
	return (cmd);
}

/*
** Entree : la chaine de caractere entree dans le prompt et captee par readline
** Sortie : une liste de t_cmd
** On parcourt la chaine de caractere jusqu'a tomber sur | > <
** On split la sous-chaine correspondante avec le separateur ' '
** Les chaines splitees representent les commandes et les arguments
que l'on stocke alors dans t_cmd ctmp->cmd
** On stocke dans ctmp->flag le flag correspondant
(0 s'il n'y a ni pipe ni redirection)
*/
t_list	*get_cmds(char *s, t_list *env_list)
{
	t_list	*cmd_list;
	t_cmd	*ctmp;
	char	*tmp;
	int		start;
	int		i;

	i = 0;
	cmd_list = NULL;
	while (s[i])
	{
		start = i;
		i = check_flag(s, i);
		tmp = ft_substr(s, start, i - start);
		ctmp = init_cmd();
		ctmp->cmd = lst_to_tab(tmp, env_list);
		ctmp->flag = get_flag(&s[i]);
		free(tmp);
		if (ctmp->flag == DLR || ctmp->flag == DRR)
			i++;
		ft_lstadd_back(&cmd_list, ft_lstnew(ctmp));
		if (s[i])
			i++;
	}
	return (cmd_list);
}
