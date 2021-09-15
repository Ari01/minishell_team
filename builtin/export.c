/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:28:22 by xuwang            #+#    #+#             */
/*   Updated: 2021/09/15 14:09:26 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
in ordre, 
with arg before '='must a-z, A_Z, -   (exmple: export a.b=1 -->no  export ab=1%.c -->yes) 
add declare -x , value after '=' add ""
export a A BC 1 -->yes  bash: export: `1': not a valid identifier
export "ab e"  -->no  bash: export: `ab e': not a valid identifier
export "ab=e" -->yes
export 1 2 -->no
            bash: export: `1': not a valid identifier
            bash: export: `2': not a valid identifier
export A=1 1 A -->yes bash: export: `1': not a valid identifier (A=1) 
$ export A=1  A=3 -->yes change A=3
*/
static int check_is_name(char *s) //problem
{
    int i;

    i = 0;
    while(s[i])
    {
        if (s[i] == '=')
            break;
        if (!(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z') && s[i] != '_' )
            return (0);
        i++;
    }
    return (1);
}

static int check_change(char *s)
{
    int i = 0;
    while(s[i])
    {
        if (s[i] == '=')
            return (1);
        i++;
    }
    return (0);
}
static t_list *check_name_exist(char *cmd, t_list *env_list) 
{
    int len;

    len = 0;
    while (cmd[len] && cmd[len] != '=') //len of env name 
        len++;
    while (env_list)   //check one env in env_list
    {
        if (ft_strncmp(cmd, (char *)env_list->content, len) == 0 && 
            (((char *)env_list->content)[len] == '\0' || ((char *)env_list->content)[len] == '='))
        {
            return (env_list);
        }
        env_list = env_list->next;
    }
    return (NULL);
}

void	print_env_list(t_list *env_list)
{
	char	*s;

	while (env_list)
	{
		s = (char *)env_list->content;
		printf("%s\n", s);
		env_list = env_list->next;
	}
}

static void add_chang_export(char *cmd, t_list *env_list)  //add or change one envin env_list
{
    t_list *to_change;

    to_change = check_name_exist(cmd, env_list);
    /* add env */
    if (check_is_name(cmd) && to_change == NULL) 
    {
        ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(cmd)));
    }
    /* change env */
    else if (check_is_name(cmd) && to_change != NULL && (check_change(cmd))) //problem!!!
    {
        to_change->content = (void *)cmd;
    } 
}

static void print_export(char *str)
{
    int i;

    i = 0;
    ft_putstr_fd("declare -x ", STDOUT_FILENO);
    while (str && str[i])
    {
        if (str[i] == '=')
        {
            ft_putchar_fd('=', STDOUT_FILENO);
            ft_putchar_fd('\"', STDOUT_FILENO);
        }
        else
            ft_putchar_fd(str[i], STDOUT_FILENO);
        i++;
    }
    if (ft_strchr(str, '='))
        ft_putchar_fd('\"', STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
}

void ft_export(t_cmd *cmd, t_list *env_list)
{
    int i;
    int j;

    j = 1;
    while (cmd && cmd->cmd[j]) 
    {
        if (!(check_is_name(cmd->cmd[j])))
           printerror("minishell: export: `", cmd->cmd[j],  "\': not a valid identifier");
        j++;
    }
    i = 1;
    while (cmd && cmd->cmd[i]) 
    {
        add_chang_export(cmd->cmd[i], env_list);
        i++;
    }
    ft_list_sort(&env_list, &ft_strcmp);
    while (cmd->cmd[1] == NULL && env_list && env_list->content)
    {
        print_export((char *)env_list->content);
        env_list = env_list->next;
    }
}
