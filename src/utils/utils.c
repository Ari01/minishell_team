/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:36:52 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/18 09:37:40 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_array_len(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

void	remove_elem_from_array(char **array)
{
	int		i;

	i = 0;
	free(array[i]);
	while (array[i])
	{
		array[i] = array[i + 1];
		i++;
	}
}

void	remove_from_list(t_list **head, t_list *elem)
{
	t_list	*ite;
	t_list	*tmp;

	ite = *head;
	if (ite == elem)
	{
		tmp = (*head)->next;
		ft_lstdelone(*head, &free_cmd);
		*head = tmp;
	}
	else
	{
		while (ite && ite->next != elem)
			ite = ite->next;
		if (!ite)
			return ;
		tmp = ite->next->next;
		ft_lstdelone(ite->next, &free_cmd);
		ite->next = tmp;
	}
}

char	**array_join(char **a1, char **a2)
{
	char	**join;
	int		len1;
	int		len2;
	int		i;
	int		j;

	len1 = get_array_len(a1);
	len2 = get_array_len(a2);
	join = malloc(sizeof(*join) * (len1 + len2 + 1));
	i = 0;
	j = 0;
	while (a1[i])
		join[j++] = ft_strdup(a1[i++]);
	i = 0;
	while (a2[i])
		join[j++] = ft_strdup(a2[i++]);
	join[j] = 0;
	return (join);
}
