/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:42:50 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/07 19:39:17 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_chdir(DIR *dir, char *file_name)
{
	struct dirent	*dirent;

	dirent = readdir(dir);
	while (dirent != NULL)
	{
		if (!ft_strcmp(dirent->d_name, file_name))
			return (1);
		dirent = readdir(dir);
	}
	closedir(dir);
	return (0);
}

char	*get_exec_path(t_ms *ms, char *cmd)
{
	int				i;
	char			*path;
	char			*tmp;
	char			**split;
	DIR				*dir;

	i = 0;
	path = get_var(ms->env_list, "PATH");
	split = ft_split(path, ":");
	while (split[i])
	{
		dir = opendir(split[i]);
		if (dir == NULL)
		{
			
			print_error_msg(strerror(errno), errno, ms);
		}
		if (ft_chdir(dir, cmd))
		{
			tmp = ft_strjoin("/", cmd);
			path = ft_strjoin(split[i], tmp);
			free(tmp);
			free_array(split);
			return (path);
		}
		i++;
	}
	return (NULL);
}

int		ft_execve(t_ms *ms, char *path, char **argv, char **envp)
{
	int		pid;
	int		signal;

	pid = fork();
	if (pid == -1)
		print_error_msg(strerror(errno), errno, ms);
	if (!pid)
	{
		if (execve(path, argv, envp) == -1)
		{
			printf("minishell: %s: command not found\n", path);
			//perror(path);
		}
		exit(errno);
	}
	else
	{
		waitpid(pid, &signal, 0);
		//printf("signal = %d\n", signal);
	}
	return (signal);
}

// execve (char *path, char **arg, char **envp)
// envp a ete mis a NULL pour les tests mais il faudra le modifier pour prendre la liste d'env var
int		run_exec(t_ms *ms, t_cmd *cmd)
{
	char	*path;
	int		ret;

	if (ft_strchr(cmd->cmd[0], '/'))
		ret = ft_execve(ms, cmd->cmd[0], cmd->cmd, NULL);
	else
	{
		path = get_exec_path(ms, cmd->cmd[0]);
		if (path)
			ret = ft_execve(ms, path, cmd->cmd, NULL);
		else
			ret = ft_execve(ms, cmd->cmd[0], cmd->cmd, NULL);
	}
	return (ret);
}
