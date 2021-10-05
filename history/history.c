/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:28:34 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/17 19:17:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void creat_history(t_history *history)  
{
    char *home;
    char *path = NULL;

    home = NULL;
    if (!home || (open(home, O_RDONLY) == -1))
    { 
        if (home)
            free(home);
        home = getcwd(NULL, 0);
    }
    //或者当前地址
    path = ft_strjoin(home, "/.minishell_history"); //地址名字
    history->path = path;
    //printf ("path:%s\n", history->path);   //path:/Users/xuwang/minishell_team/.minishell_history
    history->fd = open(history->path, O_RDWR | O_CREAT | O_APPEND, 0777);  //creat history
    //printf ("fd:%d\n", history->fd);   //fd:3
    if (history->fd == -1)
        return ;
   
}
//add old history to new file
static void add_exist_history(t_history *history)
{
    char *line;
    int read;
    
    read = 1;
    while (read > 0)
    {
        read = get_next_line(history->fd, &line);
        add_history(line);
        free(line);
        line = NULL;
    }
}

//init ./minishell_history
t_history  init_history(t_history history)
{
    creat_history(&history);
    add_exist_history(&history);   
    return (history);
}

//add new cmd
void ft_add_history(char *cmd, t_history history)
{ 
    if (!cmd || !ft_strlen(cmd))
        return ;
    if ((open(history.path, O_RDONLY)) == -1) //check is aleady exist
    {
        history.fd = open(history.path, O_RDWR | O_CREAT | O_APPEND, 0777);
        if (history.fd == -1)
            return ;
    }
    ft_putendl_fd(cmd, history.fd);   //把命令写入fd
    add_history(cmd);  //add systeme
}
