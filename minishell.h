/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:44 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/10 13:30:15 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

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
**	PARSING
*/
t_list	*get_cmds(char *s);

/*
**  BUILTINS
*/
void    ft_echo(t_cmd *cmd);

#endif
