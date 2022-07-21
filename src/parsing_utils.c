#include "../include/minishell.h"

int	cnt_tokens(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void	put_arg_pos(t_parsing *parse_list)
{
	int	i;

	i = 0;
	while (parse_list->tkns_list->tkn)
	{
		if (parse_list->tkns_list->tkn == NULL)
			break ;
		parse_list->tkns_list->argv_pos = i;
		parse_list->tkns_list = parse_list->tkns_list->next;
		i++;
	}
	parse_list->tkns_list->next = NULL;
	parse_list->tkns_list->tkn = NULL;
	parse_list->tkns_list = parse_list->tkns_list->start;
	return ;
}

int	ft_strlen_delim(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '&' || str[i] != '|' || str[i] != '<')
	{
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (i);
}
