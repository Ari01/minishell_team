/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:15:24 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/14 16:20:50 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *s)
{
	char	**split;
	int		i;

	split = ft_split(BUILTINS, ' ');
	i = 0;
	while (split[i])
	{
		if (!ft_strcmp(s, split[i]))
			return (1);
		i++;
	}
	return (0);
}
