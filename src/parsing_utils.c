#include "../include/minishell.h"

int	init_first_token_nodes(t_parsing *parse_list)  //lets see if this is even useful now
{
	parse_list->tkns_list = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->prev = NULL;
	parse_list->tkns_list->argv_pos = 0;
	parse_list->tkns_list->start = parse_list->tkns_list;
	return (0);
}

void	print_tkns_array_debug(t_parsing parse_list)
{
	int	i;

	i = 0;
	parse_list.tkns_list = parse_list.tkns_list->start;
	while (parse_list.tkns_list)
	{
		if (parse_list.tkns_list == NULL)
			return ;
		while (parse_list.tkns_list->vector_cmd
			&& parse_list.tkns_list->vector_cmd[i])
		{
			printf("list %d array %d : %s\n", parse_list.tkns_list->argv_pos,
				i, parse_list.tkns_list->vector_cmd[i]);
			i++;
		}
		parse_list.tkns_list = parse_list.tkns_list->next;
		i = 0;
	}
}

int	count_cmd(char **tkns_array, int ind_array)  //find how many tokens are type command
{
	int	count;

	count = 0;
	while (tkns_array[ind_array])
	{
		if (ft_strchr("<>", tkns_array[ind_array][0]))
		{
			ind_array += 2;
			continue ;
		}
		if (ft_strchr("|", tkns_array[ind_array][0]))
			return (count);
		count++;
		ind_array++;
	}
	return (count);
}

int	check_file_and_delim_name(t_tkns *tkns_array, int j) //this should work as-is
{
	if (tkns_array->next != NULL)
	{
		if (ft_strchr("<|>", tkns_array->next->data))
		{
			printf("Dundershell: syntax error near unexpected token `%c'\n",
				tkns_array->next->data);
			return (1);
		}
	}
	if (!tkns_array->next
		|| tkns_array->data[j + 1] != '\0')
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	check_pipe_name(t_tkns *tkns_array, int j) //this should work as-is
{
	if (tkns_array->next
		&& tkns_array->next->data[0] == '|')
	{
		printf("Dundershell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (!tkns_array->next
		|| tkns_array->next->data[j + 1] != '\0')
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
