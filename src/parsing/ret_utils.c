/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:33:30 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/07 18:41:53 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_wstatus(int status)
{
	return (status & 0177);
}

int	_wifexited(int status)
{
	return (_wstatus(status) == 0);
}

#if __DARWIN_UNIX03

int	_wexitstatus(int status)
{
	return ((status >> 8) & 0x000000ff);
}
#else

int	_wexitstatus(int status)
{
	return (status >> 8);
}

#endif
