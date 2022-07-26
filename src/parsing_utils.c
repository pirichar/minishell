#include "../include/minishell.h"

int	init_first_token_nodes(t_parsing *parse_list)
{
	parse_list->tkns_list = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->prev = NULL;
	parse_list->tkns_list->argv_pos = 0;
	parse_list->tkns_list->start = parse_list->tkns_list;
	return (0);
}

void	print_tkns_array_debug(t_parsing *parse_list)
{
	int	i;

	i = 0;
	parse_list->tkns_list = parse_list->tkns_list->start;
	while (parse_list->tkns_list)
	{
		if (parse_list->tkns_list == NULL)
			return ;
		while (parse_list->tkns_list->vector_cmd && parse_list->tkns_list->vector_cmd[i])
		{
			printf("list %d array %d : %s\n", parse_list->tkns_list->argv_pos, i ,parse_list->tkns_list->vector_cmd[i]);
			i++;
		}
		parse_list->tkns_list = parse_list->tkns_list->next;
		i = 0;
	}
}

int	count_cmd(t_parsing *parse_list)
{
	int	count;
	int	index_arr;

	count = 0;
	index_arr = 0;
	while (parse_list->tkns_array[index_arr] != NULL)
	{
		if (ft_strchr("<>", parse_list->tkns_array[index_arr][0]))
		{
			index_arr += 2;
			continue ;
		}
		count++;
		index_arr++;
	}
	return (count);
}
