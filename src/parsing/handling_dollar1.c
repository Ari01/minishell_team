/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:54:05 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/19 16:36:56 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms	g_ms;

void	part1_dollar(char *cmd, t_dollar *dolinfo)
{
	if (cmd[dolinfo->i] != '\0' && cmd[dolinfo->i] != ' '
		&& cmd[dolinfo->i] != '$')
	{
		dolinfo->start = dolinfo->i;
		while (cmd[dolinfo->i] && cmd[dolinfo->i] != '\0'
			&& cmd[dolinfo->i] != ' ' && cmd[dolinfo->i] != '$')
			++dolinfo->i;
		dolinfo->new_cmd = ft_join(dolinfo->new_cmd,
				ft_substr(cmd, dolinfo->start, dolinfo->i - dolinfo->start));
		if (cmd[dolinfo->i] == '$')
			--dolinfo->i;
	}
}

void	part2_dollar(char *cmd, t_list *env_list, t_dollar *dolinfo)
{
	while (cmd[dolinfo->i + dolinfo->len]
		&& cmd[dolinfo->i + dolinfo->len] != ' '
		&& cmd[dolinfo->i + dolinfo->len] != '\0'
		&& cmd[dolinfo->i + dolinfo->len] != '$' )
		dolinfo->len++;
	dolinfo->dollar = ft_substr(cmd, dolinfo->start, dolinfo->len);
	env_list = check_env_exit(dolinfo->dollar, env_list);
	if (env_list != NULL)
		dolinfo->new_cmd = ft_join(dolinfo->new_cmd,
				ft_substr((char *)env_list->content,
					check_env_start((char *)env_list->content),
					check_env_len((char *)env_list->content)));
	else
		dolinfo->new_cmd = ft_join(dolinfo->new_cmd, "");
	dolinfo->i = dolinfo->i + dolinfo->len - 1;
}

void	part3_dollar(char *cmd, t_list *env_list, t_dollar *dolinfo)
{
	char	*tmp;

	tmp = NULL;
	if (cmd[dolinfo->i] >= '0' && cmd[dolinfo->i] <= '9')
	{
		dolinfo->new_cmd = ft_join(dolinfo->new_cmd, "");
		++dolinfo->i;
		part1_dollar(cmd, dolinfo);
	}
	else if (cmd[dolinfo->i] == '?')
	{
		tmp = ft_itoa(g_ms.cmd_ret);
		dolinfo->new_cmd = ft_join(dolinfo->new_cmd, tmp);
		free(tmp);
		++dolinfo->i;
		if (cmd[dolinfo->i] == '$')
			--dolinfo->i;
	}
	else
	{
		dolinfo->start = dolinfo->i;
		part2_dollar(cmd, env_list, dolinfo);
	}
}

char	*hanlding_dollar(char *cmd, t_list *env_list)
{
	t_dollar	dolinfo;

	ft_bzero(&dolinfo, sizeof(t_dollar));
	while (cmd[dolinfo.i])
	{
		if (cmd[dolinfo.i] == '$' && cmd[dolinfo.i + 1] != ' '
			&& cmd[dolinfo.i + 1] != '\0' && cmd[dolinfo.i + 1] != '$')
		{
			dolinfo.i++;
			part3_dollar(cmd, env_list, &dolinfo);
		}
		else
		{
			dolinfo.c = ft_substr(cmd, dolinfo.i, 1);
			dolinfo.new_cmd = ft_join(dolinfo.new_cmd, dolinfo.c);
			free(dolinfo.c);
			dolinfo.c = NULL;
		}
		dolinfo.start = 0;
		dolinfo.len = 0;
		dolinfo.i++;
	}
	return (dolinfo.new_cmd);
}
