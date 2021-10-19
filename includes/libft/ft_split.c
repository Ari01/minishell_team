/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:07:17 by user42            #+#    #+#             */
/*   Updated: 2021/10/13 10:22:22 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	get_nwords(char const *s, char *charset)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		while (s[i] && ft_strchr(charset, s[i]))
			i++;
		if (s[i])
			ret++;
		while (s[i] && !ft_strchr(charset, s[i]))
			i++;
	}
	return (ret);
}

char	**ft_split(char const *s, char *charset)
{
	char	**split;
	int		start;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s || !charset)
		return (NULL);
	split = malloc(sizeof(*split) * (get_nwords(s, charset) + 1));
	while (s[i])
	{
		while (s[i] && ft_strchr(charset, s[i]))
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && !ft_strchr(charset, s[i]))
				i++;
			split[j] = ft_substr(s, start, i - start);
			j++;
		}
	}
	split[j] = 0;
	return (split);
}
