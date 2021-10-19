/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:46:47 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/06 19:46:55 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

int	_wifsignaled(int status)
{
	return (_wstatus(status) != 0177 && _wstatus(status) != 0);
}

int	_wtermsig(int status)
{
	return (_wstatus(status));
}
