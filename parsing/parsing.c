#include "minishell.h"

int		is_flag(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int		get_flag(char *s)
{
	if (!is_flag(*s))
		return (0);
	if (*s == '<' && (*(s + 1) == '<'))
		return (DLR);
	if (*s == '>' && (*(s + 1) == '<'))
		return (DRR);
	return (*s);
}

int		check_rdl(t_ms *ms)
{
	if (ms->rdl[0] == '|')
	{
		printf("parsing error\n");
		free_memory(ms);
		return (0);
	}
	if (!ms->cmd_list_ite)
		return (0);
	return (1);
}

t_list	*get_cmds(char *s)
{
	t_list	*cmd_list;
	t_cmd	*ctmp;
	char	*tmp;
	int		start;
	int		i;

	i = 0;
	cmd_list = NULL;
	ctmp = NULL;
	while (s[i])
	{
		start = i;
		while (s[i] && !is_flag(s[i]))
			i++;
		tmp = ft_substr(s, start, i - start);
		ctmp = malloc(sizeof(*ctmp));
		ctmp->cmd = ft_split(tmp, ' ');
		ctmp->flag = get_flag(&s[i]);
		if (ctmp->flag == DLR || ctmp->flag == DRR)
			i++;
		free(tmp);
		tmp = NULL;
		ft_lstadd_back(&cmd_list, ft_lstnew(ctmp));
		i++;
	}
	return (cmd_list);
}
