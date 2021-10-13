/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:27:37 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/06 19:29:44 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#if defined(__APPLE__) && defined(__MACH__)

void	ft_interrupt(int signe)
{
	if (signe == SIGINT && EINTR == errno)
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		ft_putstr_fd("prompt> ", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
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
	}
}

#endif
