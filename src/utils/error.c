/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:21:15 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/31 18:17:03 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms	g_ms;

void	check_exit(t_ms *ms)
{
	if (!ms->rdl)
	{
		rl_clear_history();
		ft_lstclear(&ms->env_list, &free);
		close(ms->history.fd);
		free(ms->history.path);
		free(ms->error_file_path);
		free(ms->heredoc_file_path);
		print_error_msg("exit", 0, ms);
	}
}

int	check_parsing(t_ms *ms, t_list *token_list)
{
	char	*check;

	check = check_grammar(token_list);
	if (check)
	{
		printf("minishell: erreur de syntaxe près du symbole inattendu « %s »\n",
			check);
		free(ms->rdl);
		ms->rdl = NULL;
		g_ms.cmd_ret = 2;
		return (1);
	}
	return (0);
}

int	check_error(t_ms *ms)
{
	int		ret;
	t_list	*token_list;

	check_exit(ms);
	token_list = NULL;
	token_list = get_tokens(ms->rdl);
	ret = check_parsing(ms, token_list);
	ft_lstclear(&token_list, &free_token);
	return (ret);
}

void	print_error_msg(char *s, int error_id, t_ms *ms)
{
	printf("%s\n", s);
	free_memory(ms);
	exit(error_id);
}
