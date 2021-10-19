/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 18:30:08 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/13 10:49:33 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(t_list *token_list)
{
	t_token	*token;
	t_token	*next_token;

	token = (t_token *)token_list->content;
	if (!token_list->next)
		return (0);
	next_token = (t_token *)token_list->next->content;
	if (next_token->id != CMD_TOK)
		return (0);
	return (1);
}

char	*check_pipe(t_list *token_list)
{
	t_token	*token;

	token = (t_token *)token_list->content;
	if (!token_list->next)
		return (token->value);
	token = (t_token *)token_list->next->content;
	if (token->id == PIPE_TOK)
		return (token->value);
	return (NULL);
}

t_list	*check_cmd(t_list *token_list, char **error_pos)
{
	t_token	*token;

	token = (t_token *)token_list->content;
	while (token_list && token->id == REDIR_TOK)
	{
		if (!check_redir(token_list))
		{
			*error_pos = token->value;
			return (NULL);
		}
		token_list = token_list->next->next;
		if (token_list)
			token = (t_token *)token_list->content;
	}
	if (token_list && token->id == PIPE_TOK)
	{
		*error_pos = check_pipe(token_list);
		if (*error_pos)
			return (NULL);
		token_list = token_list->next;
		token = (t_token *)token_list->content;
	}
	else if (token_list)
		token_list = token_list->next;
	return (token_list);
}

char	*check_grammar(t_list *token_list)
{
	t_token	*token;
	char	*ret;

	ret = NULL;
	while (token_list)
	{
		token = (t_token *)token_list->content;
		if (token->id == PIPE_TOK)
			return (token->value);
		else if (token->id == REDIR_TOK)
		{
			if (!check_redir(token_list))
				return (token->value);
			token_list = token_list->next;
		}
		else if (token_list->next)
		{
			token_list = check_cmd(token_list->next, &ret);
			if (!token_list)
				return (ret);
		}
		else
			token_list = token_list->next;
	}
	return (NULL);
}
