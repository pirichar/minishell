#include "../include/minishell.h"

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
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return ;
}

int	start_parse(char *line)
{
	t_parsing	*parse_list;

	parse_list = init_master_list();
	parse_list->tkns_array = split(line);
	if (parse_list->tkns_array == NULL)
		return (1);
	init_first_token_nodes(parse_list);
	init_all_token_nodes(parse_list);
	put_arg_pos(parse_list);
	check_tokens(parse_list);
	print_node_debug(parse_list);
	return (0);
}

int	init_first_token_nodes(t_parsing *parse_list)
{
	parse_list->tkns_list = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->flags = 400; //400 correspond a aucun flags de setter, a NULL
	parse_list->tkns_list->prev = NULL;
	parse_list->tkns_list->start = parse_list->tkns_list;
	return (0);
}

void	init_circular_list(t_parsing *parse_list)
{
	parse_list->tkns_list->tkn[parse_list->i_str_list] = '\0';
	if (parse_list->tkns_list->tkn == NULL)
		parse_list->tkns_list = parse_list->tkns_list->prev;
	parse_list->index_array++;
	parse_list->tkns_list->next = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->next->prev = parse_list->tkns_list;
	(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
	parse_list->tkns_list = parse_list->tkns_list->next;
	parse_list->tkns_list->dollar_sign = false;
	return ;
}
