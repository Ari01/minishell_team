/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:26:01 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/07 17:52:02 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_name(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			break ;
		if (!(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z')
			&& s[i] != '_' )
			return (0);
		i++;
	}
	return (1);
}

int	check_change(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_list	*check_name_exist(char *cmd, t_list *env_list)
{
	int	len;

	len = 0;
	while (cmd[len] && cmd[len] != '=')
		len++;
	while (env_list)
	{
		if (ft_strncmp(cmd, (char *)env_list->content, len) == 0
			&& (((char *)env_list->content)[len] == '\0'
				|| ((char *)env_list->content)[len] == '='))
		{
			return (env_list);
		}
		env_list = env_list->next;
	}
	return (NULL);
}
