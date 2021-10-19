/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:03:36 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/18 09:42:52 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, int id)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	token->value = ft_strdup(value);
	token->id = id;
	return (token);
}

int	add_redir_tok(t_list **tok_list, char redir, char next)
{
	t_token	*token;
	int		ret;

	token = malloc(sizeof(*token));
	if (redir == next)
	{
		token->value = malloc(3);
		token->value[0] = redir;
		token->value[1] = next;
		token->value[2] = 0;
		ret = 2;
	}
	else
	{
		token->value = malloc(2);
		token->value[0] = redir;
		token->value[1] = 0;
		ret = 1;
	}
	token->id = REDIR_TOK;
	ft_lstadd_back(tok_list, ft_lstnew(token));
	return (ret);
}

void	add_substr_tok(t_list **token_list, char *s, int start, int len)
{
	t_token	*token;
	char	*sub;
	char	*tmp;

	if (len > 0)
	{
		sub = ft_substr(s, start, len);
		tmp = ft_strtrim(sub, " \t\v\f\r");
		free(sub);
		if (tmp && tmp[0])
		{
			token = new_token(tmp, CMD_TOK);
			ft_lstadd_back(token_list, ft_lstnew(token));
		}
		free(tmp);
	}
}

t_list	*get_tokens(char *s)
{
	int		i;
	int		start;
	t_list	*token_list;

	i = 0;
	start = 0;
	token_list = NULL;
	while (s[i])
	{
		while (s[i] && s[i] != '|' && s[i] != '<' && s[i] != '>')
			i++;
		add_substr_tok(&token_list, s, start, i - start);
		if (s[i] == '|')
		{
			ft_lstadd_back(&token_list, ft_lstnew(new_token("|", PIPE_TOK)));
			i++;
		}
		else if (s[i] == '<' || s[i] == '>')
			i += add_redir_tok(&token_list, s[i], s[i + 1]);
		start = i;
	}
	return (token_list);
}
