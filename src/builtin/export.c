/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:28:22 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/31 17:45:51 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_chang_export(char *cmd, t_list *env_list)
{
	t_list	*to_change;

	to_change = check_name_exist(cmd, env_list);
	if (check_is_name(cmd) && to_change == NULL)
		ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(cmd)));
	else if (check_is_name(cmd) && to_change != NULL && (check_change(cmd)))
	{
		free(to_change->content);
		to_change->content = ft_strdup(cmd);
	}
}

static void	print_export(char *str)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	while (str && str[i])
	{
		if (str[i] == '=')
		{
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		else
			ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
	if (str && ft_strchr(str, '=') != NULL)
		ft_putchar_fd('\"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	check_export(t_cmd *cmd, int ret)
{
	int	i;

	i = 1;
	while (cmd && cmd->cmd[i])
	{
		if (!(check_is_name(cmd->cmd[i])))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(cmd->cmd[i], STDERR_FILENO);
			ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
			ret = ERROR;
		}
		i++;
	}
	return (ret);
}

int	ft_export(t_cmd *cmd, t_list *env_list)
{
	int	i;
	int	ret;

	ret = SUCCESS;
	if (!cmd)
		return (ERROR);
	ret = check_export(cmd, ret);
	i = 1;
	while (cmd && cmd->cmd[i])
		add_chang_export(cmd->cmd[i++], env_list);
	ft_list_sort(&env_list, &ft_strcmp);
	while (cmd && cmd->cmd[1] == NULL && env_list && env_list->content)
	{
		print_export((char *)env_list->content);
		env_list = env_list->next;
	}
	return (ret);
}
