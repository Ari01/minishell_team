/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:41:18 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/15 16:52:31 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_len(const char *s)
{
	const char	*str;

	if (!s)
		return (0);
	str = s;
	while (*str)
		++str;
	return (str - s);
}

char	*ft_join(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	len = ft_len(s1) + ft_len(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		*str++ = s1[i++];
	i = 0;
	while (s2 && s2[i])
		*str++ = s2[i++];
	*str = '\0';
	if (s1)
		free((char *)s1);
	return (str - len);
}

t_cmdinfo	*creat_cmdinfo(void)
{
	t_cmdinfo	*cmdinfo;

	cmdinfo = malloc(sizeof(t_cmdinfo));
	if (cmdinfo)
	{
		cmdinfo->cmd = NULL;
		cmdinfo->status = NO_TOUCH;
	}
	return (cmdinfo);
}
