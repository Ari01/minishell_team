#include "minishell.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}
void ft_echo(t_cmd *cmd)
{
    int i;
    int n;

    n = 0;
    i = 1;
    while (cmd && cmd->cmd[i] && (ft_strcmp(cmd->cmd[i], "-n") == 0))
    {
        i++;
        n = 1;
    }
    while (cmd && cmd->cmd[i])
    {
        printf("%s", cmd->cmd[i]);
        if (cmd->cmd[i + 1])
            printf(" ");
        else if(!cmd->cmd[i + 1] && n == 0)
            printf("\n");
        i++;
    }
}

// void ft_cd(t_cmd *cmd)
// {

// }

// int main(void) 
// {
//     t_cmd *echo_cmd;

//     echo_cmd = malloc(sizeof(t_cmd));
//     char *cmd[4];

//     cmd[0] = "echo";
//     cmd[1] = "-n";
//     cmd[2] = "world";
//     cmd[3] = NULL;

//     echo_cmd->cmd = cmd;
//     ft_echo(echo_cmd);
//     free(echo_cmd);
//     return 0;
// }
