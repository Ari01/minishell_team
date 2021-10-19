/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quot1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:34:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/19 15:52:46 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_list	*_part1_(t_quotinfo *quotinfo, char *cmd,
		t_list *env_list)
{
	t_list	*ret3;

	ret3 = NULL;
	if (cmd[quotinfo->i] == '"')
	{
		quotinfo->i++;
		ret3 = part_dq(cmd, env_list, quotinfo);
		if (ret3 != NULL)
			return (ret3);
	}
	return (NULL);
}

static	t_list	*sepa_part(t_quotinfo *quotinfo, char *cmd,
		t_list *env_list)
{
	t_list	*ret;

	ret = NULL;
	while (cmd[quotinfo->i])
	{
		if (cmd[quotinfo->i] != '\''
			&& cmd[quotinfo->i] != '"' && cmd[quotinfo->i] != ' ')
		{
			ret = part_nq(cmd, env_list, quotinfo);
			if (ret != NULL)
				return (ret);
		}
		if (cmd[quotinfo->i] == '\'')
		{
			quotinfo->i++;
			ret = part_sq(cmd, quotinfo);
			if (ret != NULL)
				return (ret);
		}
		ret = _part1_(quotinfo, cmd, env_list);
		if (ret != NULL)
			return (ret);
		++quotinfo->i;
	}
	return (quotinfo->list1);
}

t_list	*sepa_cmd(char *cmd, t_list *env_list)
{
	t_quotinfo	quotinfo;
	t_list		*ret;

	ft_bzero(&quotinfo, sizeof(t_quotinfo));
	ret = NULL;
	while (cmd && cmd[quotinfo.i] && cmd[quotinfo.i] == ' ')
		++quotinfo.i;
	ret = sepa_part(&quotinfo, cmd, env_list);
	return (ret);
}
