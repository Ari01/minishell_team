/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:57:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/13 20:58:35 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_var_list(t_list *env_list)
{
	while (env_list)
	{
		printf("%s\n", (char *)env_list->content);
		env_list = env_list->next;
	}
}

char	*get_var(t_list *env_list, char *name)
{
	char	*ret;

	ret = NULL;
	while (env_list)
	{
		ret = (char *)env_list->content;
		if (!ft_strncmp(ret, name, ft_strlen(name)))
			return (ret + ft_strlen(name) + 1);
		env_list = env_list->next;
	}
	return (ret);
}
