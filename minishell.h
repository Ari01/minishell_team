#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
    char    **cmd;
    int     flag;
}   t_cmd;

#endif