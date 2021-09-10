/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:44 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/10 16:02:02 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

/*
**	ERRORS DEF
*/
# define SYNTAX_ERR 1
# define PIPE_ERR	2

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
typedef struct s_cmd
{
    char    **cmd;
    int     flag;
}   t_cmd;

/*
**	ERRORS
*/
void	print_error_msg(char *s, int error_id);

/*
**	PARSING
*/
t_list	*get_cmds(char *s);

/*
**	PIPE
*/
void	run_pipe(t_list *cmd_list);

/*
**  BUILTINS
*/
void    ft_echo(t_cmd *cmd);

/*
**	COMMANDS
*/
void	run_cmd(t_cmd *cmd);

#endif
