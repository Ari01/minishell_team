/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:58:59 by user42            #+#    #+#             */
/*   Updated: 2021/10/11 14:47:50 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	get_nb_len(int n)
{
	size_t			len;
	unsigned int	unbr;

	len = 1;
	unbr = n;
	if (n < 0)
	{
		len++;
		unbr = -n;
	}
	if (unbr < 10)
		return (len);
	while (unbr)
	{ 
		unbr = unbr / 10;
		len++;
	}
	return (len);
	/*	int	i;

	if (n == 0)
		i = 1;
	else
		i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);*/
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
	s[0] = '0';
	if (n < 0)
	{
		unbr = -n;
		s[0] = '-';
	}
	s[len] = 0;
	while (unbr)
	{
		s[--len] = unbr % 10 + '0';
		unbr = unbr / 10;
	}
	return (s);
}
