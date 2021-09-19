/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:53:02 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/19 19:18:01 by xuwang           ###   ########.fr       */
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
	ctmp = NULL;
	while (s[i])
	{
		start = i;
		while (s[i] && !is_flag(s[i]))
			i++;
		tmp = ft_substr(s, start, i - start);
		ctmp = malloc(sizeof(*ctmp));
		ctmp->cmd = ft_split(tmp, ' ');
		ctmp->flag = get_flag(&s[i]);
		if (ctmp->flag == DLR || ctmp->flag == DRR)
			i++;
		free(tmp);
		tmp = NULL;
		ft_lstadd_back(&cmd_list, ft_lstnew(ctmp));
		i++;
	}
	return (cmd_list);
}
