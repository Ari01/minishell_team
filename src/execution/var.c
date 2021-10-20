/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:57:12 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/20 06:27:29 by dchheang         ###   ########.fr       */
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
	int		len;

	ret = NULL;
	len = ft_strlen(name);
	while (env_list)
	{
		ret = (char *)env_list->content;
		if (!ft_strncmp(ret, name, len))
			return (ret + len + 1);
		env_list = env_list->next;
	}
	return (ret);
}
