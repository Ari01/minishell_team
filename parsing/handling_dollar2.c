/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:41:18 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/12 17:43:15 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dollar(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

t_list	*check_env_exit(char *dollar, t_list *env_list)
{
	int	len;

	len = ft_strlen(dollar);
	while (env_list)
	{
		if (ft_strncmp(dollar, (char *)env_list->content, len) == 0
			&& (((char *)env_list->content)[len] == '\0'
			|| ((char *)env_list->content)[len] == '='))
		{
			return (env_list);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

int	check_env_start(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i + 1);
}

int	check_env_len(char *env)
{
	int	start;
	int	len;
	int	i;

	start = check_env_start(env);
	len = ft_strlen(env);
	i = len - start;
	return (i);
}
