/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:58:59 by user42            #+#    #+#             */
/*   Updated: 2021/10/13 14:38:16 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	get_nb_len(int n)
{
	size_t			len;
	unsigned int	unbr;

	len = 0;
	unbr = n;
	if (n < 0)
	{
		len++;
		unbr = -n;
	}
	if (unbr < 10)
		return (1);
	while (unbr)
	{
		unbr = unbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*s;
	int				i;
	size_t			len;
	unsigned int	unbr;

	i = 0;
	unbr = n;
	len = get_nb_len(n);
	s = malloc(sizeof(*s) * (len + 1));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		unbr = -n;
		s[0] = '-';
	}
	s[len] = 0;
	while (len--)
	{
		s[len] = unbr % 10 + '0';
		unbr = unbr / 10;
	}
	return (s);
}
