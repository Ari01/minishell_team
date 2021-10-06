/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:42:50 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/06 19:53:35 by dchheang         ###   ########.fr       */
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

void	ft_execve(t_ms *ms, char *path, char **argv, char **envp)
{
	int		pid;
	char	*error_msg;
	char	*freeptr;

	pid = fork();
	if (pid == -1)
		print_error_msg(strerror(errno), errno, ms);
	if (!pid)
	{
		if (execve(path, argv, envp) == -1)
		{
			if (errno == 2)
			{
				error_msg = "minishel: ";
				error_msg = ft_strjoin(error_msg, path);
				freeptr = error_msg;
				error_msg = ft_strjoin(error_msg, ": command not found");
				print_error_msg(error_msg, 5, ms);
			}
			else
				print_error_msg(strerror(errno), errno, ms);
			exit(EXIT_SUCCESS);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

// execve (char *path, char **arg, char **envp)
// envp a ete mis a NULL pour les tests mais il faudra le modifier pour prendre la liste d'env var
void	run_exec(t_ms *ms, t_cmd *cmd)
{
	char	*path;

	if (ft_strchr(cmd->cmd[0], '/'))
		ft_execve(ms, cmd->cmd[0], cmd->cmd, NULL);
	else
	{
		path = get_exec_path(ms, cmd->cmd[0]);
		if (path)
			ft_execve(ms, path, cmd->cmd, NULL);
		else
			ft_execve(ms, cmd->cmd[0], cmd->cmd, NULL);
	}
}
