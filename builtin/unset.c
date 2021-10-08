/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:53:21 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/04 16:56:04 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_is_cmd(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z')
			&& s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static t_list	*check_exist(char *cmd, t_list *env_list)
{
	int	len;

	len = 0;
	if (check_is_cmd(cmd))
	{
		len = ft_strlen(cmd);
	}
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

static t_list	*del_env(char *cmd, t_list *env_list)
{
	t_list	*to_del;
	t_list	*tmp;
	t_list	*prev;

	prev = NULL;
	tmp = env_list;
	to_del = check_exist(cmd, env_list);
	if (!to_del)
		return (env_list);
	while (tmp && tmp != to_del)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == to_del)
	{
		if (prev == NULL)
			env_list = tmp->next;
		else
			prev->next = tmp->next;
		if (tmp)
		{
			free(tmp->content);
			tmp->content = NULL;
			free(tmp);
			tmp = NULL;
		}
	}
	return (env_list);
}

int	ft_unset(t_cmd *cmd, t_list **env_list)
{
	int	i;

	i = 1;
	if (!cmd || !cmd->cmd[1])
		return (ERROR);
	while (cmd && cmd->cmd[i])
	{
		if (!(check_is_cmd(cmd->cmd[i])))
			print_msg("minishell: unset: `", cmd->cmd[i],
				"\': not a valid identifier\n", STDERR_FILENO);
		else
			*env_list = del_env(cmd->cmd[i], *env_list);
		i++;
	}
	return (SUCCESS);
}
