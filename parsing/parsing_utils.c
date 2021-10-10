/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:41:18 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/26 18:47:45 by xuwang           ###   ########.fr       */
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

	cmdinfo = NULL;
	cmdinfo = malloc (sizeof(t_cmd));
	if (cmdinfo)
	{
		cmdinfo->cmd = NULL;
		cmdinfo->status = NO_TOUCH;
	}
	return (cmdinfo);
}

t_quot	quote_init(void)
{
	t_quot	quote_info;

	quote_info.quot = NO_Q;
	quote_info.quot_status = STATUS_CLOSE;
	return (quote_info);
}

static void	check_part1(t_quot *quot, int i)
{	
	if (i == 1)
		quot->quot = IS_SQ;
	else if (i == 0)
		quot->quot = IS_DQ;
	if (quot->quot_status == STATUS_CLOSE)
		quot->quot_status = STATUS_OPEN;
	else
	{
		quot->quot_status = STATUS_CLOSE;
		quot->quot = NO_Q;
	}
}

int	check_flag(char *cmd, int i)
{
	t_quot	quot;

	quot = quote_init();
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			if (quot.quot == IS_DQ)
			{
				++i;
				continue ;
			}
			check_part1(&quot, 1);
		}
		else if (cmd[i] == '"')
		{
			if (quot.quot == IS_SQ)
			{
				++i;
				continue ;
			}
			check_part1(&quot, 0);
		}
		if (is_flag(cmd[i]) && quot.quot_status == STATUS_CLOSE)
			return (i);
		i++;
	}
	return (i);
}
