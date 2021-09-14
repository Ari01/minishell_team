/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:28:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/14 20:05:26 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void creat_history(void)
{
    char *path; 
    char *home; //ficher
    int fd;
    //check 文件在不在
    
    //home = getenv("HOME");
    printf("the home path is %s\n", home); ///Users/xuwang
    if (!home || !open(home, O_RDONLY))   //find "HOME"
    { 
        if (home)
            free(home);
        home = getcwd(NULL, 0); 
         printf("the home path is %s\n", home);
    }
    //split
    path = home + ./minishell_history
    free(home);
    fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0777);  //creat history
    if (!fd)
        return (ERROR);
    //命名   O_RDWR | O_CREAT | O_APPEND, __DEFAULT_RIGHTS__
    //O_RDWR以可读写方式打开文件   O_APPEND就是所写入的数据会以附加的方式加入到文件后面.
}

//添加命令行add_history

//初始之前的命令
// static void add_history()
// {
    
// }

// void	*ft_memdel(void **ptr)
// {
// 	if (ptr && *ptr)
// 	{
// 		free(*ptr);
// 		*ptr = NULL;
// 	}
// 	return (NULL);
//}


// void ft_add_history(char *cmd, int fd)
// {
    
//     ft_putendl_fd(cmd, fd);   //把命令写入fd
//     add_history(cmd);
// }

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
   char *home;
   home = putcwd(NULL, 0); 
   
   printf("the home path is %s\n", );
    if(argc != 2)
    { 
        printf("param error"); 
        return 1;
    }
    else
    { 
        int fd = open(*(argv+1), O_RDONLY | O_CREAT, 0777);
        if(fd != -1){ printf("%s is created.\n",*(argv+1)); }
    }
    return 0;
}