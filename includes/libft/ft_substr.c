/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:33:21 by user42            #+#    #+#             */
/*   Updated: 2021/10/15 16:46:44 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (len + 1 <= 0)
		len = 0;
	sub = malloc(sizeof(*sub) * (len + 1));
	if (!sub || !s)
	{
		if (!s && sub)
			free(sub);
		return (NULL);
	}
	i = 0;
	if (start < ft_strlen(s))
	{
		while (i < len && s[start])
		{
			sub[i] = s[start];
			start++;
			i++;
		}
	}
	sub[i] = '\0';
	return (sub);
}
