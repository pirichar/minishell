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

int	init_first_token_nodes(t_parsing *parse_list)
{
	parse_list->tkns_list = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->flags = 400; //400 correspond a aucun flags de setter, a NULL
	parse_list->tkns_list->prev = NULL;
	parse_list->tkns_list->start = parse_list->tkns_list;
	return (0);
}

int	init_all_token_nodes(t_parsing *parse_list)
{
	while (cnt_tokens(parse_list->tkns_array) > parse_list->index_array)
	{
		split_by_delims(parse_list);




		
		// parse_list->tkns_list->tkn = calloc(ft_strlen_delim(
		// 			(parse_list->tkns_array[parse_list->index_array]))
		// 		+ 1, sizeof(char));
		// init_circular_list(parse_list);
	}
	parse_list->tkns_list = parse_list->tkns_list->start;
	return (0);
}
