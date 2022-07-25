#include "../include/minishell.h"

int	init_first_token_nodes(t_parsing *parse_list)
{
	parse_list->tkns_list = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->prev = NULL;
	parse_list->tkns_list->start = parse_list->tkns_list;
	return (0);
}

t_parsing	*init_master_list(void)
{
	t_parsing	*parse_list;

	parse_list = calloc(1, sizeof(t_parsing));
	return (parse_list);
}













// void	print_node_debug(t_parsing *parse_list)
// {
// 	while (parse_list->tkns_list->tkn != NULL)
// 	{
// 		printf("tkns = %s, arg pos = %d, flags = %d, is dollar sign? = %d\n",
// 			parse_list->tkns_list->tkn,
// 			parse_list->tkns_list->argv_pos, parse_list->tkns_list->flags,
// 			parse_list->tkns_list->dollar_sign);
// 		if (parse_list->tkns_list->next == NULL)
// 			break ;
// 		parse_list->tkns_list = parse_list->tkns_list->next;
// 	}
// 	return ;
// }

// void	prep_next_node(t_parsing *parse_list)
// {
// 	parse_list->tkns_list->next = calloc(1, sizeof(t_tkns));
// 	parse_list->tkns_list->next->start = parse_list->tkns_list->start;
// 	parse_list->tkns_list->next->prev = parse_list->tkns_list;
// 	parse_list->tkns_list = parse_list->tkns_list->next;
// 	parse_list->tkns_list->tkn = calloc(ft_strlen_without_delim(
// 				parse_list->tkns_array[parse_list->index_array]), sizeof(char));
// 	parse_list->index_str_array = 0;
// }