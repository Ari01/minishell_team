/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:21:24 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/12 17:34:56 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*gnl_strjoin(char const *s1, char const *s2)
{
	t_gnl	gnl;

	ft_bzero(&gnl, sizeof(t_gnl));
	if (!s1 && !s2)
		return (0);
	if (s1)
		gnl.len1 = ft_strlen(s1);
	else
		gnl.len1 = 0;
	gnl.len2 = ft_strlen(s2);
	gnl.len = gnl.len1 + gnl.len2 + 1;
	gnl.tab = (char *)malloc(sizeof(char) * gnl.len);
	if (!gnl.tab)
		return (NULL);
	while (s1 && gnl.i < gnl.len && s1[gnl.i])
	{
		gnl.tab[gnl.i] = s1[gnl.i];
		gnl.i++;
	}
	while (s2 && gnl.i < gnl.len && s2[gnl.j])
		gnl.tab[gnl.i++] = s2[gnl.j++];
	gnl.tab[gnl.i] = '\0';
	free((char *)s1);
	return (gnl.tab);
}

static char	*first_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*save_line(char *save)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (0);
	}
	str = (char *)malloc(sizeof(char) * ft_strlen(save) - i + 1);
	if (!str)
		return (NULL);
	i++;
	while (save[i])
		str[j++] = save[i++];
	free(save);
	str[j] = '\0';
	return (str);
}

static int	ft_newline(char *save)
{
	int	i;

	i = 0;
	if (!save)
		return (0);
	while (save[i])
	{
		if (save[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			read_num;
	static char	*save;

	read_num = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while (read_num != 0 && !ft_newline(save))
	{
		read_num = read(fd, buf, BUFFER_SIZE);
		if (read_num == -1)
			return (-1);
		buf[read_num] = '\0';
		save = gnl_strjoin(save, buf);
	}
	*line = first_line(save);
	save = save_line(save);
	if (read_num == 0)
		return (0);
	return (1);
}
