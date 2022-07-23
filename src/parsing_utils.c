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

t_parsing	*init_master_list(void)
{
	t_parsing	*parse_list;

	parse_list = calloc(1, sizeof(t_parsing));
	parse_list->index_array = 0;
	parse_list->index_str_array = 0;
	parse_list->i_str_list = 0;
	return (parse_list);
}

void	print_node_debug(t_parsing *parse_list)
{
	while (parse_list->tkns_list->tkn != NULL)
	{
		printf("tkns = %s, arg pos = %d, flags = %d, is dollar sign? = %d\n",
			parse_list->tkns_list->tkn,
			parse_list->tkns_list->argv_pos, parse_list->tkns_list->flags,
			parse_list->tkns_list->dollar_sign);
		if (parse_list->tkns_list->next == NULL)
			break ;
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return ;
}

int	print_syntax_err_simple(t_parsing *parse_list, char c)
{
	if (parse_list->index_str_array == 0)
	{
		printf("DunderShell: syntax error near unexpected token `%.1s'\n",
			parse_list->tkns_array[parse_list->index_array]);
		return (1);
	}
	else if (parse_list->tkns_array[parse_list->index_array][parse_list->index_str_array + 2] == '\0')
	{
		while (*parse_list->tkns_array[parse_list->index_array] != c)
			parse_list->tkns_array[parse_list->index_array]++;
		printf("DunderShell: syntax error near unexpected token `%.1s'\n",
			parse_list->tkns_array[parse_list->index_array]);
		return (1);
	}
	return (0);
}

int	print_syntax_err_double(t_parsing *parse_list, char c)
{
	printf("line la %s\n", parse_list->tkns_array[parse_list->index_array]);
	if (parse_list->tkns_list->tkn == NULL)
	{
		printf("DunderShell: syntax error near unexpected token `%.2s'\n",
			parse_list->tkns_array[parse_list->index_array]);
		return (1);
	}
	else if (parse_list->tkns_array[parse_list->index_array][parse_list->index_str_array + 2]  == '\0')
	{
		while (*parse_list->tkns_array[parse_list->index_array] != c)
		{
			parse_list->tkns_array[parse_list->index_array]++;
		}
		printf("DunderShell: syntax error near unexpected token `%.2s'\n",
			parse_list->tkns_array[parse_list->index_array]);
		return (1);
	}
	return (0);
}

int	print_syntax_err_full(t_parsing *parse_list, char c)
{
	if (parse_list->index_str_array == 0)
	{
		printf("DunderShell: syntax error near unexpected token `%s'\n",
			parse_list->tkns_array[parse_list->index_array]);
		return (1);
	}
	if (parse_list->tkns_array[parse_list->index_array][parse_list->index_str_array + 2] == '\0')
	{
		while (*parse_list->tkns_array[parse_list->index_array] != c)
			parse_list->tkns_array[parse_list->index_array]++;
		printf("DunderShell: syntax error near unexpected token `%s'\n",
			parse_list->tkns_array[parse_list->index_array]);
		return (1);
	}
	return (0);
}
