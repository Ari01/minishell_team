/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:15:24 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/06 19:59:15 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *s)
{
	char	**split;
	int		i;

	split = ft_split(BUILTINS, " ");
	i = 0;
	while (split[i])
	{
		if (!ft_strcmp(s, split[i]))
		{
			free_array(split);
			return (1);
		}
		i++;
	}
	free_array(split);
	return (0);
}
