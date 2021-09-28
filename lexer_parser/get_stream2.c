/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stream2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:29:21 by dchheang          #+#    #+#             */
/*   Updated: 2021/09/28 16:30:13 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_operator(char *token_value)
{
	if (!ft_strcmp(token_value, "<"))
		return ('<');
	if (!ft_strcmp(token_value, ">"))
		return ('>');
	if (!ft_strcmp(token_value, ">>"))
		return (DRR);
	if (!ft_strcmp(token_value, "<<"))
		return (DLR);
	return (-1);
}

t_op	*new_op(char *left, char *right, char *operator)
{
	t_op	*op;

	op = malloc(sizeof(*op));
	op->left = NULL;
	op->right = NULL;
	if (left)
		op->left = ft_strdup(left);
	if (right)
		op->right = ft_strdup(right);
	if (operator)
	{
		printf("operator = %s\n", operator);
		if (!ft_strcmp(operator, "<"))
			op->op = '<';
		else if (!ft_strcmp(operator, ">"))
			op->op = '>';
		else if (!ft_strcmp(operator, "|"))
			op->op = '|';
		else if (!ft_strcmp(operator, ">>"))
			op->op = DRR;
		else if (!ft_strcmp(operator, "<<"))
			op->op = DLR;
		else
			op->op = -1;
	}
	return (op);
}

t_list	*get_op(t_list *token_list)
{
	t_op	*op;
	t_token	*current_token;
	t_token	*next_token;
	t_token	*next_next_token;
	t_list	*op_list;

	op_list = NULL;
	while (token_list)
	{
		current_token = (t_token *)token_list->content;
		if (current_token->id == REDIR_TOK)
		{
			op = new_op(NULL, next_token->value, current_token->value);
			token_list = token_list->next->next;
		}
		else if (token_list->next)
		{
			next_token = (t_token *)token_list->next->content;
			next_next_token = (t_token *)token_list->next->next->content;
			op = new_op(current_token->value, next_next_token->value, next_token->value);
			token_list = token_list->next->next;
		}
		else
			op = new_op(current_token->value, NULL, NULL);
		ft_lstadd_back(&op_list, ft_lstnew(op));
		token_list = token_list->next;
	}
	return (op_list);
}
