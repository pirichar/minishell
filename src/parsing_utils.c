#include "../include/minishell.h"

int	init_first_token_nodes(t_parsing *parse_list)  //may 21, should be ok. but is it useful
{
	parse_list->tkns_list = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->prev = NULL;
//	parse_list->tkns_list->argv_pos = 0;
	parse_list->start = NULL;
	return (0);
}

// void	print_tkns_array_debug(t_parsing parse_list)
// {
// 	int	i;

// 	i = 0;
// 	parse_list.tkns_list = parse_list.tkns_list->start;
// 	while (parse_list.tkns_list)
// 	{
// 		if (parse_list.tkns_list == NULL)
// 			return ;
// 		while (parse_list.tkns_list->vector_cmd
// 			&& parse_list.tkns_list->vector_cmd[i])
// 		{
// 			printf("list %d array %d : %s\n", parse_list.tkns_list->argv_pos,
// 				i, parse_list.tkns_list->vector_cmd[i]);
// 			i++;
// 		}
// 		parse_list.tkns_list = parse_list.tkns_list->next;
// 		i = 0;
// 	}
// }

int	count_cmd(t_tkns *tkns_list)  //is it still used?
{
	int	count;

	count = 0;
	while (tkns_list != NULL)
	{
		count++;
		tkns_list = tkns_list->next;
	}
	return (count);
}

int	check_file_and_delim_name(t_tkns *tkns_list)
{
	if (tkns_list->next != NULL)
	{
		if (ft_strchr("<|>", tkns_list->next->data[0])) 
		{
			printf("Dundershell: syntax error near unexpected token `%c'\n",
				tkns_list->next->data[0]);
			return (1);
		}
	}
	if (!tkns_list->next || tkns_list->next->data == NULL)
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	check_pipe_name(t_tkns *tkns_list) //may 21, should be ok
{
	if (tkns_list->next
		&& tkns_list->next->data[0] == '|')
	{
		printf("Dundershell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (!tkns_list->next || tkns_list->next->data == NULL)
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
