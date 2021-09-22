/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:31:01 by user42            #+#    #+#             */
/*   Updated: 2021/09/22 18:20:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_array(t_list *token_list, int len)
{
	int		i;
	char	**array;
	t_token	token;

	i = 0;
	array = malloc(sizeof(*array) * (len + 1));
	while (i < len)
	{
		token = *(t_token *)token_list->content;
		array[i] = ft_strdup(token.id);
		token_list = token_list->next;
		i++;
	}
	array[i] = 0;
	return (array);
}

t_cmd	*get_stream(t_list *token_list, t_cmd *cmd)
{
	t_token	token;

	token = *(t_token *)token_list->next->content;
	if (cmd->flag == SLR || cmd->flag == DLR)
		cmd->in_stream = ft_strdup(token->value);
	else
		cmd->out_stream = ft_strdup(token->value);
	return (cmd);
}

t_list	*add_redir_cmd(t_list **cmd_list, t_list *i, t_list *j, t_token token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!ft_strcmp(token.value, "<<"))
		cmd->flag = DLR;
	else if (!ft_strcmp(token.value, ">>"))
		cmd->flag = DRR;
	else
		cmd->flag = token.value;
	cmd = get_stream(i, cmd);
	cmd->cmd = get_array(j, i - j);
	ft_lstadd_back(cmd_list, ft_lstnew(cmd));
	i = i->next->next;
	return (i);
}

t_list	*add_cmd(t_list **cmd_list, t_list *i, t_list *j, int flag)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->cmd = get_array(j, i - j);
	cmd->flag = flag;
	cmd->out_stream = NULL;
	cmd->in_stream = NULL;
	ft_lstadd_back(cmd_list, ft_lstnew(cmd));
	i = i->next;
	return (i);
}

t_list	*get_cmds(t_list *token_list)
{
	t_list	*i;
	t_list	*j;
	t_list	*cmd_list;
	t_token	current_token;

	cmd_list = NULL;
	i = token_list;
	while (i)
	{
		j = i;
		current_token = *(t_token *)i->content;
		while (i && current_token.id == CMD_TOK)
		{
			i = i->next;
			if (i)
				current_token = *(t_token *)i->content;
		}
		if (i && current_token.id == REDIR_TOK)
			i = add_redir_cmd(&cmd_list, i, j, current_token);
		else if (i && current_token.id == PIPE_TOK)
			i = add_cmd(&cmd_list, i, j, PIPE);
		else
			add_cmd(&cmd_list, i, j, 0);
	}
	return (cmd_list);
}
