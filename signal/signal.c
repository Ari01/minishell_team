/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:27:37 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/16 15:44:46 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_interrupt(int signe)
{
    if (signe == SIGQUIT) //ctrl-\  删除已有字符 (循环中不能使用)
    {
         ft_putstr_fd("exit\n", STDIN_FILENO);
    }
    
    if (signe == SIGINT) //ctrl-c  \n 另起一行 强制终止程序的执行
    {
        
    }
   
    if (signe == D)  //Ctrl+D：不是发送信号 作用相当于在终端中输入exit后回车；(循环中不能使用)
    {
       
        
    }

errno == EINTR