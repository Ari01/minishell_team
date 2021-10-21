/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:41 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/20 11:13:46 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_fds(t_ms *ms)
{
	dup2(ms->fd_in, STDIN_FILENO);
	dup2(ms->fd_out, STDOUT_FILENO);
	dup2(ms->fd_err, STDERR_FILENO);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_interrupt);
	run_shell(env);
	return (0);
}
