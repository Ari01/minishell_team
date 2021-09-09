/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:53:02 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/09 17:22:31 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_separator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int		get_flag(char *s)
{
	if (!is_separator(*s))
		return (0);
	if (*s == '<' && (*(s + 1) == '<'))
		return (DLR);
	if (*s == '>' && (*(s + 1) == '<'))
		return (DRR);
	return (*s);
}

t_list	*get_cmds(char *s)
{
	t_list	*cmd_list;
	t_cmd	*ctmp;
	char	*tmp;
	int		start;
	int		i;

	i = 0;
	while (s[i])
	{
		start = i;
		while (s[i] && !is_separator(s[i]))
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
