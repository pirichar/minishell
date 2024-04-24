// #include "../include/minishell.h"

// int	start_parse(char *line)
// {
// 	t_parsing	*parse_list;

// 	parse_list = init_master_list();
// 	parse_list->tkns_array = split(line);
// 	if (parse_list->tkns_array == NULL)
// 		return (1);
// 	init_first_token_nodes(parse_list);
	
// 	init_all_token_nodes(parse_list);
// 	put_arg_pos(parse_list);
// 	check_tokens(parse_list);
// 	argv0(parse_list);
// 	print_node_debug(parse_list);
// 	return (0);
// }
