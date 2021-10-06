/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:33:30 by xuwang            #+#    #+#             */
/*   Updated: 2021/10/06 16:36:17 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//1，WIFEXITED(status) 这个宏用来指出子进程是否为正常退出的，如果是，它会返回一个非零值。
//2，WEXITSTATUS(status) 当WIFEXITED返回非零值时，我们可以用这个宏来提取子进程的返回值，
//   如果子进程调用exit(5)退出，WEXITSTATUS(status)就会返回5；如果子进程调用exit(7)，
//   WEXITSTATUS(status)就会返回7。请注意，如果进程不是正常退出的，也就是说，WIFEXITED返回0，这个值就毫无意义。
// 代码截取x的最低7位：x &0177

#define _WSTATUS(x)     (_W_INT(x) & 0177)
#define _WSTOPPED       0177            /* _WSTATUS if process is stopped */
#if __DARWIN_UNIX03
#define WEXITSTATUS(x)  ((_W_INT(x) >> 8) & 0x000000ff)
#else /* !__DARWIN_UNIX03 */
#define WEXITSTATUS(x)  (_W_INT(x) >> 8)