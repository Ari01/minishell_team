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

static int	check_part2(char *cmd, int i, t_quot *quot)
{
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			if (quot->quot == IS_DQ)
			{
				++i;
				continue ;
			}
			check_part1(quot, 1);
		}
		else if (cmd[i] == '"')
		{
			if (quot->quot == IS_SQ)
			{
				++i;
				continue ;
			}
			check_part1(quot, 0);
		}
		if (is_flag(cmd[i]) && quot->quot_status == STATUS_CLOSE)
			return (i);
		i++;
	}
	return (i);
}

int	check_flag(char *cmd, int i)
{
	t_quot	quot;
	int		ret;

	quot = quote_init();
	ret = check_part2(cmd, i, &quot);
	return (ret);
}
