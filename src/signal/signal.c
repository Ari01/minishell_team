/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:27:37 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/19 15:49:13 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_cmd_ret;

#if defined(__APPLE__) && defined(__MACH__)

void	ft_interrupt(int signe)
{
	if (signe == SIGINT && EINTR == errno)
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		ft_putstr_fd("prompt> ", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_cmd_ret = 130;
	}
}

#else 

void	ft_interrupt(int signe)
{
	if (signe == SIGINT && EINTR == errno)
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_cmd_ret = 130;
	}
}

#endif
