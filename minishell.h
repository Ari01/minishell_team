/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:44 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/11 20:10:19 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include <assert.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"

# define PIPE '|'
# define SLR '<'
# define DLR 1
# define SRR '>'
# define DRR 2

# define ERROR -1
# define SUCCESS 0
/*
** STRUCT
*/
typedef struct s_cmd
{
    char    **cmd;
    int     flag;
}   t_cmd;


/*
**	PARSING
*/
t_list	*get_cmds(char *s);

/*
**  BUILTINS
*/
void    ft_echo(t_cmd *cmd);
int     ft_cd(t_cmd *cmd);
void    ft_pwd(t_cmd *cmd);
void    ft_exit(void);
void    ft_env(t_list *env_list);
void    ft_export(t_cmd *cmd, t_list *env_list);
void    printerror(char *msg1, char *msg2, char *msg3);
t_list  *get_env(char **env, t_list *env_list);

#endif
