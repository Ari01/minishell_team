/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:02:40 by user42            #+#    #+#             */
/*   Updated: 2021/09/12 15:50:25 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// int		ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t i;

// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i] && i + 1 < n)
// 		i++;
// 	if (n > 0)
// 		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 	return (0);
// }
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && (*s1 == *s2) && n > 0)
	{
		++s1;
		++s2;
		n--;
	}
	if (n)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}