/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:44 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/12 17:16:39 by user42           ###   ########.fr       */
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
void	run_cmd(t_cmd *cmd);

/*
**	UTILS
*/
void	remove_elem_from_array(char **array);

#endif
