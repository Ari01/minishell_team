/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:44 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/13 17:30:47 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
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

/*
**	ERRORS DEF
*/
# define SYNTAX_ERR		1
# define PIPE_ERR		2
# define FILE_ERR		3
# define READ_WRITE_ERR 4

/*
**	READ WRITE DEF
*/
# define BUFFER_SIZE 100000

/*
**	PIPE AND REDIRECTION DEF
*/
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
typedef struct s_ms
{
	char	*rdl;
	int		fd_in;
	int		fd_out;
	t_list	*cmd_list_head;
	t_list	*cmd_list_ite;
	t_list	*env_list;
}	t_ms;

typedef struct s_cmd
{
    char    **cmd;
    int     flag;
}   t_cmd;


/*
**	ERRORS
*/
void	free_memory(t_ms *ms);
void	print_error_msg(char *s, int error_id, t_ms *ms);

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
void    ft_unset(t_cmd *cmd, t_list *env_list);
/*
**  UTILS
*/
t_list  *get_env(char **env, t_list *env_list);
void    ft_list_sort(t_list **begin_list, int (*ft_strcmp)());
void    printerror(char *msg1, char *msg2, char *msg3);


/*
**	PIPE
*/
void	run_pipe(t_ms *ms);

/*
**	REDIRECTION
*/
void	reset_fdin_fdout(t_ms *ms);
void	redirect(t_ms *ms, t_cmd current_cmd);

/*
**	COMMANDS
*/
void	run_cmd(t_ms *ms, t_cmd *cmd);

/*
**	UTILS
*/
void	remove_elem_from_array(char **array);

#endif
