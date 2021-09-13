/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:42:50 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/13 20:56:50 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_exec_path(t_ms *ms, char *cmd)
{
	int				i;
	char			*path;
	char			**split;
	DIR				*dir;
	struct dirent	*dirent;

	i = 0;
	path = get_var(ms->env_list, "PATH");
	split = ft_split(path, ':');
	while (split[i])
	{
		dir = opendir(split[i]);
		if (dir == NULL)
			print_error_msg(strerror(errno), EXEC_ERR, ms);
		dirent = readdir(dir);
		while (dirent != NULL)
		{
			if (!ft_strcmp(dirent->d_name, cmd))
			{
				path = ft_strdup(split[i]);
				free_array(split);
				return (path);
			}
			dirent = readdir(dir);
		}
		closedir(dir);
		i++;
	}
	return (NULL);
}

// execve (char *path, char **arg, char **envp)
// envp a ete mis a NULL pour les tests mais il faudra le modifier pour prendre la liste d'env var
void	run_exec(t_ms *ms, t_cmd *cmd)
{
	char	*tmp;
	char	*freeptr;
	char	*path;

	if (ft_strchr(cmd->cmd[0], '/'))
	{
		if (execve(cmd->cmd[0], &cmd->cmd[1], NULL) == -1)
			print_error_msg(strerror(errno), EXEC_ERR, ms);
	}
	else
	{
		path = get_exec_path(ms, cmd->cmd[0]);
		tmp = ft_strjoin("/", cmd->cmd[0]);
		freeptr = path;
		path = ft_strjoin(path, tmp);
		free(tmp);
		if (execve(path, &cmd->cmd[1], NULL) == -1)
			print_error_msg(strerror(errno), EXEC_ERR, ms);
	}
}
