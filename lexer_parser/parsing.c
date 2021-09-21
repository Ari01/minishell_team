/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:53:02 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/21 19:43:39 by dchheang         ###   ########.fr       */
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

/*
int		get_stream(t_cmd **cmd, char **s, int start)
{
	int	i;

	i = start;
	if ((*cmd)->flag == SLR || (*cmd)->flag == SRR)
		i++;
	else if ((*cmd)->flag == DLR || (*cmd)->flag == DRR)
		i += 2;
	else
		return (s);
	while (s[i] && s[i] != ' ')
		i++;
	(*cmd)->stream = ft_substr(s, start, i - start);
	while (s[i])
	{
		s[start] = s[i];
		start++;
		i++;
	}
	s[start] = 0;
	return (s);
}*/

/*
** Entree : la chaine de caractere entree dans le prompt et captee par readline
** Sortie : une liste de t_cmd
** On parcourt la chaine de caractere jusqu'a tomber sur un caractere pipe ou redirection '|', '<' ou '>'
** On recupere la sous-chaine correspondante, que l'on split a l'aide du separateur ' '
** Les chaines splitees representent les commandes et les arguments, que l'on stocke alors dans t_cmd ctmp->cmd
** Ensuite, on regarde si la sous-chaine se termine par une pipe ou une redirection ou non
** On stocke dans ctmp->flag le flag correspondant (0 s'il n'y a ni pipe ni redirection)
*/
t_list	*get_cmds(char *s)
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
		while (s[i] && !is_flag(s[i]))
			i++;
		tmp = ft_substr(s, start, i - start);
		ctmp = malloc(sizeof(*ctmp));
		ctmp->cmd = ft_split(tmp, " ");
		ctmp->flag = get_flag(&s[i]);
		ctmp->in_stream = NULL;
		ctmp->out_stream = NULL;
		free(tmp);
		tmp = NULL;
		ft_lstadd_back(&cmd_list, ft_lstnew(ctmp));
		if (ctmp->flag == DLR || ctmp->flag == DRR)
			i++;
		if (s[i])
			i++;
	}
	return (cmd_list);
}

void	get_stream(t_list **cmd_list)
{
	t_cmd	*cmd;
	t_cmd	*next_cmd;
	t_list	*ite;
	t_list	*tmp;
	char	**join;

	ite = *cmd_list;
	cmd = NULL;
	while (ite)
	{
		cmd = (t_cmd *)ite->content;
		if (cmd->flag == SLR || cmd->flag == DLR
			|| cmd->flag == SRR || cmd->flag == DRR)
		{
			next_cmd = (t_cmd *)ite->next->content;
			if (!cmd->cmd[0])
			{
				next_cmd->stream = ft_strdup(next_cmd->cmd[0]);
				remove_elem_from_array(next_cmd->cmd);
				ite = ite->next;
			}
			else
			{
				cmd->stream = next_cmd->cmd[0];
				if (next_cmd->cmd[1])
				{
					remove_elem_from_array(next_cmd->cmd);
					join = array_join(cmd->cmd, next_cmd->cmd);
					free_array(cmd->cmd);
					cmd->cmd = join;
				}
				tmp = ite->next;
				ite = ite->next->next;
				remove_from_list(cmd_list, tmp);
			}
		}
		else
			ite = ite->next;
	}
}
