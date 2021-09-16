/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:27:37 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/16 19:13:35 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#if defined(__APPLE__) && defined(__MACH__)

void    ft_interrupt(int signe)
{
    if (signe == SIGQUIT) //ctrl D 退出信号 
    {
        
       
        ft_putstr_fd("exit\n", STDIN_FILENO);
        return ;
        //exit (0);
        //  //printf("%s", readline(NULL));
        
    }
    
    if (signe == SIGINT && EINTR == errno) //ctrl-c  \n 另起一行 中断信号 errno == EINTR
    {
        ft_putstr_fd("\n", STDIN_FILENO);
         ft_putstr_fd("prompt> ", STDIN_FILENO);        rl_on_new_line();
        //rl_replace_line("", 0);
        rl_redisplay();   //print pro
    }
    
}
// void  ft_interrupt(int signe)
// {
//     signe = getchar();
//     if (signe == EOF)
//         exit(0);
// }


#else 

void    ft_interrupt(int signe)
{
    if (signe == SIGQUIT) //ctrl D 退出信号 
    {
        
        ft_putstr_fd("exit\n", STDIN_FILENO);
        return ;
        
        //  //printf("%s", readline(NULL));
        
    }
    
    else if (signe == SIGINT && EINTR == errno) //ctrl-c  \n 另起一行 中断信号 errno == EINTR
    {
        ft_putstr_fd("\n", STDIN_FILENO);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();   //print pro
    }
}
#endif