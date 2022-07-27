#include "../include/minishell.h"

int	get_cmd(t_parsing *parse_list)
{
	parse_list->tkns_list->vector_cmd = calloc(sizeof(char **),
			count_cmd(parse_list->tkns_array, parse_list->i_arr) + 1);
	while (parse_list->tkns_array[parse_list->i_arr])
	{
		alloc_vector(parse_list, parse_list->i_vect, parse_list->i_arr, false);
		while (parse_list->tkns_array[parse_list->i_arr][parse_list->i_str])
		{
			if (is_it_redir(parse_list) == 1)
				return (0);
			else if (is_it_redir(parse_list) == 0)
				continue ;
			if (is_it_pipe(parse_list) == 0)
				continue ;
			else
				do_copy_cmd(parse_list);
		}
		parse_list->i_str = 0;
		parse_list->i_arr++;
		parse_list->i_vect++;
	}
	return (0);
}

void	init_master_list(t_parsing *parse_list)
{
	parse_list->nb_of_pipes = 0;
	parse_list->i_arr = 0;
	parse_list->i_str = 0;
	parse_list->i_vect = 0;
}

t_parsing	*start_parse(char *line)
{
	t_parsing	*parse_list;

	parse_list = calloc(1, sizeof(t_parsing));
	init_master_list(parse_list);
	init_first_token_nodes(parse_list);
	parse_list->tkns_array = ft_split(line, ' ');
	if (parse_list->tkns_array == NULL)
		return (NULL);
	init_first_token_nodes(parse_list);
	if (check_metachar(parse_list) != 0)
		return (NULL);
	get_cmd(parse_list);
	print_tkns_array_debug(parse_list);
	return (parse_list);
}

void	do_copy_cmd(t_parsing *parse_list)
{
	parse_list->tkns_list->vector_cmd[parse_list->i_vect][parse_list->i_str]
		= parse_list->tkns_array[parse_list->i_arr][parse_list->i_str];
	parse_list->i_str++;
}
